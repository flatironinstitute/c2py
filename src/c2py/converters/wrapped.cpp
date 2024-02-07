#include "./wrapped.hpp"
namespace c2py {

  // Fetch the pointer to the converter table from __main__
  std::shared_ptr<pto_table_t> get_pto_table_from_main() {
    // Fetch __main__ module
    pyref str_main = PyUnicode_FromString("__main__");
    pyref mod      = PyImport_GetModule(str_main);
    if (mod == nullptr) {
      PyErr_SetString(PyExc_RuntimeError, "Severe internal error : can not load __main__");
      throw std::runtime_error("Severe internal error : can not load __main__");
    }

    // Return ptr from __cpp2py_table attribute if available
    if (not PyObject_HasAttrString(mod, "__cpp2py_table")) return {};
    pyref capsule = PyObject_GetAttrString(mod, "__cpp2py_table");
    if (capsule.is_null()) throw std::runtime_error("Severe internal error : can not load __main__.__cpp2py_table");
    void *ptr = PyCapsule_GetPointer(capsule, "__main__.__cpp2py_table");
    return {*static_cast<std::shared_ptr<pto_table_t> *>(ptr)};
  }

  // Destructor used to clean the capsule containing the converter table pointer
  void _table_destructor(PyObject *capsule) {
    auto *p = static_cast<std::shared_ptr<pto_table_t> *>(PyCapsule_GetPointer(capsule, "__main__.__cpp2py_table"));
    delete p; //NOLINT
  }

  // Get the converter table, initialize it if necessary
  std::shared_ptr<pto_table_t> get_pto_table() {
    if (not Py_IsInitialized()) return {}; // do it later
    std::shared_ptr<pto_table_t> sptr = get_pto_table_from_main();

    // Init map if pointer in main is null
    if (not sptr) {
      sptr = std::make_shared<pto_table_t>();

      // Now register the pointer in __main__
      PyObject *mod = PyImport_GetModule(PyUnicode_FromString("__main__"));
      auto *p       = new std::shared_ptr<pto_table_t>{sptr}; //NOLINT
      pyref c       = PyCapsule_New((void *)p, "__main__.__cpp2py_table", (PyCapsule_Destructor)_table_destructor);
      pyref s       = PyUnicode_FromString("__cpp2py_table");
      int err       = PyObject_SetAttr(mod, s, c);
      if (err) {
        PyErr_SetString(PyExc_RuntimeError, "Can not add the __cpp2py_table to main");
        throw std::runtime_error("Can not add the __cpp2py_table to main");
      }
    }
    return sptr;
  }

  // get the PyTypeObject from the table in __main__.
  // if the type was not wrapped, return nullptr and set up a Python exception
  PyTypeObject *get_type_ptr(std::type_index const &ind) {
    pto_table_t &conv_table = *conv_table_sptr.get();
    //PyTypeObject *r          = nullptr;

    auto it = conv_table.find(ind.name());
    if (it != conv_table.end()) return it->second;

    std::string s = std::string{"The type "} + ind.name() + " can not be converted";
    PyErr_SetString(PyExc_RuntimeError, s.c_str());
    return nullptr;
  }

} // namespace c2py
