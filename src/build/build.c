#include <vizo/build/build.h>
#include <string.h>

package_t *package_new();

PyMODINIT_FUNC PyInit_vizo(void) {
    PyObject *m;
    if (PyType_Ready(&vizo_py_project_type) < 0)
        return NULL;
    m = PyModule_Create(&vizo_module);
    if (m == NULL)
        return NULL;

    if (PyModule_AddObjectRef(m, "Project", (PyObject *) &vizo_py_project_type) < 0) {
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

static void vizo_py_project_dealloc(vizo_py_project_t *self) {
    if (self->package != NULL) {
        package_free(self->package);
    }
    Py_TYPE(self)->tp_free((PyObject *) self);
}
PyObject *vizo_py_project_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    vizo_py_project_t *self;
    self = (vizo_py_project_t *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->package = NULL;
    }
    return (PyObject *) self;
}
int vizo_py_project_init(vizo_py_project_t *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"pkg", NULL};
    PyObject *package = NULL;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, &package)) {
        return -1;
    }
    if (package) {
        // check if the object is string
        if (PyUnicode_Check(package)) {
            const char *json_path = PyUnicode_AsUTF8(package);
            json_t *json = json_parse_file(json_path);
            if (json == (void*)-1) {
                // raise a python error
                PyErr_SetString(PyExc_IOError, "Failed to read the package file");
                return -1;
            } else if (json == (void*)-2) {
                PyErr_SetString(PyExc_ValueError, "Invalid JSON");
                return -1;
            }
            self->package = package_from_json(json);
            if (self->package == NULL) {
                return -1;
            }
        } else {
            PyErr_SetString(PyExc_TypeError, "Expected a string");
            return -1;
        }
    } else {
        self->package = package_new();
        if (self->package == NULL) {
            return -1;
        }
    }
    return 0;
}


