#include <nanobind/nanobind.h>
#include <iostream>

namespace py = nanobind;

void export_flipped_camera_2d(py::module_& m);
void export_extra_shapes(py::module_& m);


void export_raylib_extensions(py::module_& m)
{
    // submodule for raylib
    auto raylib_extension_module = m.def_submodule("raylib_extensions", "raylib extensions");
    export_flipped_camera_2d(raylib_extension_module);
    export_extra_shapes(raylib_extension_module);
}
