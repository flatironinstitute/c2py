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

    // The legacy cpp2py table, or an empty shared_ptr if no legacy module has created it. Once found
    // it is cached : a table in __main__ is never replaced. A miss is *not* cached : a legacy module
    // may well be imported after us.
    std::shared_ptr<pto_table_t> get_legacy_pto_table() {
      static std::shared_ptr<pto_table_t> cache = {}; //NOLINT
      if (cache) return cache;
      if (not Py_IsInitialized()) return {};
      cache = table_from_main(legacy_table_names);
      return cache;
    }

  } // namespace

  // Get the c2py table, initialize it if necessary
  std::shared_ptr<pto_table_t> get_pto_table() {
    if (not Py_IsInitialized()) return {}; // do it later
    auto sptr = table_from_main(c2py_table_names);
    if (not sptr) sptr = create_table_in_main(c2py_table_names);
    return sptr;
  }

  void register_pto_in_table(const char *mangled_name, PyTypeObject *pto) { (*conv_table_sptr)[mangled_name] = pto; }

  pto_lookup_t lookup_pto_in_tables(std::type_index const &ind) {
    if (conv_table_sptr) {
      auto const &table = *conv_table_sptr;
      if (auto it = table.find(ind.name()); it != table.end()) return {it->second, false};
    }
    if (auto sptr = get_legacy_pto_table(); sptr) {
      if (auto it = sptr->find(ind.name()); it != sptr->end()) return {it->second, true};
    }
    PyErr_SetString(PyExc_RuntimeError, ("The type "s + ind.name() + " can not be converted").c_str());
    return {};
  }

} // namespace c2py
