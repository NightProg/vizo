
#ifndef VIZO_BUILD_H
#define VIZO_BUILD_H

#include <Python.h>
#include <vizo/package/package.h>


typedef struct vizo_py_project {
    PyObject_HEAD
    package_t *package;
} vizo_py_project_t;


PyMODINIT_FUNC PyInit_vizo(void);
static void vizo_py_project_dealloc(vizo_py_project_t *self);
PyObject *vizo_py_project_new(PyTypeObject *type, PyObject *args, PyObject *kwds);
int vizo_py_project_init(vizo_py_project_t *self, PyObject *args, PyObject *kwds);

static PyTypeObject vizo_py_project_type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "vizo.Project",
    .tp_doc = PyDoc_STR("Project"),
    .tp_basicsize = sizeof(vizo_py_project_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = vizo_py_project_new,
    .tp_init = (initproc) vizo_py_project_init,
};

static PyModuleDef vizo_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "vizo",
    .m_doc = "Vizo package manager",
    .m_size = -1,
};


#endif //VIZO_BUILD_H
