#include <iostream>

#include <nanobind/nanobind.h>
#include <raylib.h>

// ray math
extern "C" {
#include <raylib.h>
#define RAYMATH_DISABLE_CPP_OPERATORS
#include <raymath.h>
}

// nanobind namespace
namespace nb = nanobind;
 

template<std::size_t N, class T,  class VECTOR>
void vector_add_implicit_tuple_conversion(nb::class_<VECTOR>& cls)
{
    // add the constructor
    cls.def("__init__", [](VECTOR* t, nb::tuple tup) {
        // infer the size of the vector via sizeof
        if (tup.size() != N) {
            throw std::runtime_error("constructor requires a tuple of size " + std::to_string(N));
        }
        // use some variadic shenanics
        new (t) VECTOR{};
        // reinterpret as T * 
        T* data = reinterpret_cast<T*>(t);  
        for (size_t i = 0; i < N; i++) {
            data[i] = nb::cast<T>(tup[i]);
        }
    });
    nb::implicitly_convertible<nb::tuple, VECTOR>();
}

void export_structs(nb::module_& m)
{
    // Export structs
    auto vec2 = nb::class_<Vector2>(m, "Vector2");
    vec2.def(nb::init<float, float>())
        .def_rw("x", &Vector2::x)
        .def_rw("y", &Vector2::y)
        .def("length", [](const Vector2& v) { return Vector2Length(v); }, "Get vector length")
    ;
    vector_add_implicit_tuple_conversion<2, float>(vec2);

    auto vec3 = nb::class_<Vector3>(m, "Vector3");
    vec3.def(nb::init<float, float, float>())
        .def_rw("x", &Vector3::x)
        .def_rw("y", &Vector3::y)
        .def_rw("z", &Vector3::z)
        .def("length", [](const Vector3& v) { return Vector3Length(v); }, "Get vector length")
    ;
    vector_add_implicit_tuple_conversion<3, float>(vec3);

    auto vec4 = nb::class_<Vector4>(m, "Vector4");
    vec4.def(nb::init<float, float, float, float>())
        // from tuple
        .def("__init__", [](Vector4* t, nb::tuple tup) {
            if (tup.size() != 4) { throw std::runtime_error("Vector4 constructor requires a tuple of size 4");}
            new (t) Vector4{nb::cast<float>(tup[0]), nb::cast<float>(tup[1]), nb::cast<float>(tup[2]), nb::cast<float>(tup[3])};
        })
        .def_rw("x", &Vector4::x)
        .def_rw("y", &Vector4::y)
        .def_rw("z", &Vector4::z)
        .def_rw("w", &Vector4::w)
        .def("length", [](const Vector4& v) { return Vector4Length(v); }, "Get vector length")
    ;
    vector_add_implicit_tuple_conversion<4, float>(vec4);

    auto mat4 = nb::class_<Matrix>(m, "Matrix");
    mat4.def(nb::init<>())
        .def_rw("m0", &Matrix::m0)
        .def_rw("m1", &Matrix::m1)
        .def_rw("m2", &Matrix::m2)
        .def_rw("m3", &Matrix::m3)
        .def_rw("m4", &Matrix::m4)
        .def_rw("m5", &Matrix::m5)
        .def_rw("m6", &Matrix::m6)
        .def_rw("m7", &Matrix::m7)
        .def_rw("m8", &Matrix::m8)
        .def_rw("m9", &Matrix::m9)
    ;
    // Color
    auto color = nb::class_<Color>(m, "Color");
    color.def(nb::init<unsigned char, unsigned char, unsigned char, unsigned char>())
        .def_rw("r", &Color::r)
        .def_rw("g", &Color::g)
        .def_rw("b", &Color::b)
        .def_rw("a", &Color::a)
    ;
    vector_add_implicit_tuple_conversion<4, unsigned char>(color);


    // Camera2D
    auto camera2d = nb::class_<Camera2D>(m, "Camera2D");
    camera2d.def(nb::init<>())
        .def_rw("offset", &Camera2D::offset)
        .def_rw("target", &Camera2D::target)
        .def_rw("rotation", &Camera2D::rotation)
        .def_rw("zoom", &Camera2D::zoom)
    ;
}

