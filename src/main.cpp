#include <nanobind/nanobind.h>
#include <iostream>

namespace py = nanobind;

void export_raylib(py::module_& m);
void export_raylib_extensions(py::module_& m);

NB_MODULE(_praylib, m)
{
    // raylib itself
    export_raylib(m);

    // raylib extensions
    export_raylib_extensions(m);

    m.doc() = "Praylib!";

    m.def("is_web", []() { 
        #ifdef EMSCRIPTEN
            return true;
        #else
            return false;
        #endif
    });

}
