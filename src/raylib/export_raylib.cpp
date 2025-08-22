#include <nanobind/nanobind.h>
#include <iostream>

namespace py = nanobind;

void export_structs(py::module_& m);
void export_rcore(py::module_& m);
void export_rshapes(py::module_& m);
void export_rtext(py::module_& m);

void export_raylib(py::module_& m)
{
    // submodule for raylib
    auto raylib_module = m.def_submodule("raylib", "raylib module");

    export_structs(raylib_module);
    export_rcore(raylib_module);
    export_rshapes(raylib_module);
    export_rtext(raylib_module);
}
