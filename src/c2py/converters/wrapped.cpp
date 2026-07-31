#include "./wrapped.hpp"
#include <memory>

namespace c2py {

  // Each table is stored in __main__ in a PyCapsule holding a pointer to a
  // std::shared_ptr<pto_table_t>, so that all the modules of the process share it.
  //
  // The legacy cpp2py stores its own table in exactly the same way : same capsule name, same key
  // (the mangled name given by std::type_index) and a std::map<std::string, PyTypeObject *> of the
  // same layout, so we can read and write it directly. This is an ABI coupling with cpp2py, which is
  // the price of the interoperability. cpp2py is deprecated and frozen, so it will not move.

  namespace {

    // The names under which a table is stored, so that all of the below can serve more than one.
    struct table_names_t {
      const char *attr;    // the attribute of __main__ holding the capsule
      const char *capsule; // the name of the capsule, which PyCapsule_GetPointer checks
    };

    constexpr table_names_t c2py_table_names{"__c2py_table", "__main__.__c2py_table"};
    constexpr table_names_t legacy_table_names{"__cpp2py_table", "__main__.__cpp2py_table"};

    // __main__. Throws, with a Python exception set, if it can not be found.
    pyref get_main_module_or_die() {
      pyref mod = pyref::module("__main__");
      if (mod.is_null()) throw std::runtime_error("Severe internal error : can not load __main__");
      return mod;
    }

    // Destructor of the capsule owning the shared_ptr to a table. The capsule carries its own name,
    // so the same destructor serves any table.
    void table_destructor(PyObject *capsule) {
      auto *p = static_cast<std::shared_ptr<pto_table_t> *>(PyCapsule_GetPointer(capsule, PyCapsule_GetName(capsule)));
      delete p; //NOLINT
    }

    // The table in __main__.<names.attr>, or an empty shared_ptr if the attribute is absent.
    std::shared_ptr<pto_table_t> table_from_main(table_names_t names) {
      pyref mod = get_main_module_or_die();
      if (not PyObject_HasAttrString(mod, names.attr)) return {};
      pyref capsule = PyObject_GetAttrString(mod, names.attr);
      if (capsule.is_null()) throw std::runtime_error("Severe internal error : can not load __main__."s + names.attr);
      void *ptr = PyCapsule_GetPointer(capsule, names.capsule);
      if (ptr == nullptr) throw std::runtime_error("Severe internal error : __main__."s + names.attr + " is not the expected capsule");
      return {*static_cast<std::shared_ptr<pto_table_t> *>(ptr)};
    }

    // Create an empty table and store it in __main__.<names.attr>.
    std::shared_ptr<pto_table_t> create_table_in_main(table_names_t names) {
      auto sptr = std::make_shared<pto_table_t>();
      pyref mod = get_main_module_or_die();
      // Use unique_ptr so the allocation is freed if PyCapsule_New or SetAttr fail.
      auto p_owner = std::make_unique<std::shared_ptr<pto_table_t>>(sptr);
      pyref c      = PyCapsule_New((void *)p_owner.get(), names.capsule, (PyCapsule_Destructor)table_destructor);
      if (c.is_null()) throw std::runtime_error("Can not create the "s + names.attr + " capsule");
      p_owner.release(); // the capsule now owns the raw pointer; table_destructor will delete it
      if (PyObject_SetAttrString(mod, names.attr, c) != 0) {
        PyErr_SetString(PyExc_RuntimeError, ("Can not add the "s + names.attr + " to main").c_str());
        throw std::runtime_error("Can not add the "s + names.attr + " to main");
      }
      return sptr;
    }

    // The table named by names, created if absent and create is true. Once found it is cached : a
    // table in __main__ is never replaced. A miss is *not* cached : Python may not be initialized
    // yet, and a legacy module may well be imported after us.
    std::shared_ptr<pto_table_t> get_table(table_names_t names, std::shared_ptr<pto_table_t> &cache, bool create) {
      if (cache) return cache;
      if (not Py_IsInitialized()) return {};
      auto sptr = table_from_main(names);
      if (not sptr and create) sptr = create_table_in_main(names);
      cache = sptr;
      return sptr;
    }

    // The legacy cpp2py table, or an empty shared_ptr if no legacy module has created it and create
    // is false.
    std::shared_ptr<pto_table_t> get_legacy_pto_table(bool create = false) {
      static std::shared_ptr<pto_table_t> cache = {}; //NOLINT
      return get_table(legacy_table_names, cache, create);
    }

  } // namespace

  // Get the c2py table, initialize it if necessary. Empty only if Python is not initialized yet,
  // which happens when c2py is linked into a program whose static initialization precedes
  // Py_Initialize : the callers below must then do nothing, and the first call after Py_Initialize
  // builds the table. Do not read conv_table_sptr instead : it is the copy of whichever translation
  // unit, frozen at whatever get_pto_table returned when that unit was initialized.
  std::shared_ptr<pto_table_t> get_pto_table() {
    static std::shared_ptr<pto_table_t> cache = {}; //NOLINT
    return get_table(c2py_table_names, cache, true);
  }

  PyTypeObject *register_pto_in_table(const char *mangled_name, PyTypeObject *pto) {
    auto sptr = get_pto_table();
    if (not sptr) return pto; // no interpreter : report pto as registered, so no conflict is diagnosed
    return sptr->try_emplace(mangled_name, pto).first->second;
  }

  void register_pto_in_legacy_table(const char *mangled_name, PyTypeObject *pto) {
    auto sptr = get_legacy_pto_table(true);
    if (not sptr) return; // Py_IsInitialized was false : nothing sensible to do here
    // Keeping the first registration matters here too : the legacy modules exchange objects of their
    // own Python type between themselves, and they can not recognize ours.
    sptr->try_emplace(mangled_name, pto);
  }

  pto_lookup_t lookup_pto_in_tables(std::type_index const &ind) {
    // The c2py table first : a type wrapped by a c2py module is registered in both tables, so a hit
    // here means the wrap<T> holder, whatever the legacy table holds for that type.
    if (auto sptr = get_pto_table(); sptr) {
      if (auto it = sptr->find(ind.name()); it != sptr->end()) return {it->second, false};
    }
    if (auto sptr = get_legacy_pto_table(); sptr) {
      if (auto it = sptr->find(ind.name()); it != sptr->end()) return {it->second, true};
    }
    PyErr_SetString(PyExc_RuntimeError, ("The type "s + ind.name() + " can not be converted").c_str());
    return {};
  }

} // namespace c2py
