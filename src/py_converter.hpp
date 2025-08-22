
#pragma once

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <raylib.h>

namespace nb = nanobind;


using ArrayVector2 = nb::ndarray<float, nb::numpy, nb::shape<-1, 2>, nb::c_contig>;
using ArrayVector3 = nb::ndarray<float, nb::numpy, nb::shape<-1, 3>, nb::c_contig>;
using ArrayVector4 = nb::ndarray<float, nb::numpy, nb::shape<-1, 4>, nb::c_contig>;