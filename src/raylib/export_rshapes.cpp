



#include <iostream>

#include <nanobind/nanobind.h>
extern "C" {
#include <raylib.h>
}
#include <py_converter.hpp>

// nanobind namespace
namespace nb = nanobind;



// export drawing functions
void export_rshapes(nb::module_& m)
{

    m.def("draw_pixel", &DrawPixel, "Draw a pixel using geometry [Can be slow, use with care]", nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("color"));
    m.def("draw_pixel_v", &DrawPixelV, "Draw a pixel using geometry (Vector version) [Can be slow, use with care]", nb::arg("position"), nb::arg("color"));
    m.def("draw_line", &DrawLine, "Draw a line", nb::arg("start_pos_x"), nb::arg("start_pos_y"), nb::arg("end_pos_x"), nb::arg("end_pos_y"), nb::arg("color"));
    m.def("draw_line_v", &DrawLineV, "Draw a line (using vector)", nb::arg("start"), nb::arg("end"), nb::arg("color"));
    m.def("draw_line_ex", &DrawLineEx, "Draw a line (using triangles/quads)", nb::arg("start"), nb::arg("end"), nb::arg("thick"), nb::arg("color"));
   
    
    //m.def("draw_line_strip", &DrawLineStrip, "Draw lines sequence (using gl lines)", nb::arg("points"), nb::arg("point_count"), nb::arg("color"));

    m.def("draw_line_strip", [](ArrayVector2 points, Color color) {
        DrawLineStrip(reinterpret_cast<const Vector2*>(points.data()), points.shape(0), color);
    }, "Draw lines sequence (using gl lines)", nb::arg("points"), nb::arg("color"));

    




    m.def("draw_line_bezier", &DrawLineBezier, "Draw line segment cubic-bezier in-out interpolation", nb::arg("start_pos"), nb::arg("end_pos"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_circle", &DrawCircle, "Draw a color-filled circle", nb::arg("center_x"), nb::arg("center_y"), nb::arg("radius"), nb::arg("color"));
    m.def("draw_circle_sector", &DrawCircleSector, "Draw a piece of a circle", nb::arg("center"), nb::arg("radius"), nb::arg("start_angle"), nb::arg("end_angle"), nb::arg("segments"), nb::arg("color"));  
    m.def("draw_circle_sector_lines", &DrawCircleSectorLines, "Draw circle sector outline", nb::arg("center"), nb::arg("radius"), nb::arg("start_angle"), nb::arg("end_angle"), nb::arg("segments"), nb::arg("color"));
    m.def("draw_circle_gradient", &DrawCircleGradient, "Draw a gradient-filled circle", nb::arg("center_x"), nb::arg("center_y"), nb::arg("radius"), nb::arg("inner"), nb::arg("outer"));
    m.def("draw_circle_v", &DrawCircleV, "Draw a color-filled circle (Vector version)", nb::arg("center"), nb::arg("radius"), nb::arg("color"));
    m.def("draw_circle_lines", &DrawCircleLines, "Draw circle outline", nb::arg("center_x"), nb::arg("center_y"), nb::arg("radius"), nb::arg("color"));
    m.def("draw_circle_lines_v", &DrawCircleLinesV, "Draw circle outline (Vector version)", nb::arg("center"), nb::arg("radius"), nb::arg("color"));
    m.def("draw_ellipse", &DrawEllipse, "Draw ellipse", nb::arg("center_x"), nb::arg("center_y"), nb::arg("radius_h"), nb::arg("radius_v"), nb::arg("color"));
    m.def("draw_ellipse_lines", &DrawEllipseLines, "Draw ellipse outline", nb::arg("center_x"), nb::arg("center_y"), nb::arg("radius_h"), nb::arg("radius_v"), nb::arg("color"));
    m.def("draw_ring", &DrawRing, "Draw ring", nb::arg("center"), nb::arg("inner_radius"), nb::arg("outer_radius"), nb::arg("start_angle"), nb::arg("end_angle"), nb::arg("segments"), nb::arg("color"));
    m.def("draw_ring_lines", &DrawRingLines, "Draw ring outline", nb::arg("center"), nb::arg("inner_radius"), nb::arg("outer_radius"), nb::arg("start_angle"), nb::arg("end_angle"), nb::arg("segments"), nb::arg("color"));        
    m.def("draw_rectangle", &DrawRectangle, "Draw a color-filled rectangle", nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("width"), nb::arg("height"), nb::arg("color"));
    m.def("draw_rectangle_v", &DrawRectangleV, "Draw a color-filled rectangle (Vector version)", nb::arg("position"), nb::arg("size"), nb::arg("color"));
    m.def("draw_rectangle_rec", &DrawRectangleRec, "Draw a color-filled rectangle", nb::arg("rec"), nb::arg("color"));
    m.def("draw_rectangle_pro", &DrawRectanglePro, "Draw a color-filled rectangle with pro parameters", nb::arg ("rec"), nb::arg("origin"), nb::arg("rotation"), nb::arg("color"));
    m.def("draw_rectangle_gradient_v", &DrawRectangleGradientV, "Draw a vertical-gradient-filled rectangle", nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("width"), nb::arg("height"), nb::arg("top"), nb::arg("bottom"));
    m.def("draw_rectangle_gradient_h", &DrawRectangleGradientH, "Draw a horizontal-gradient-filled rectangle", nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("width"), nb::arg("height"), nb::arg("left"), nb::arg("right"));
    m.def("draw_rectangle_gradient_ex", &DrawRectangleGradientEx, "Draw a gradient-filled rectangle with custom vertex colors", nb::arg("rec"), nb::arg("color1"), nb::arg("color2"), nb::arg("color3"), nb::arg("color4"));
    m.def("draw_rectangle_lines", &DrawRectangleLines, "Draw rectangle outline", nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("width"), nb::arg("height"), nb::arg("color"));
    m.def("draw_rectangle_lines_ex", &DrawRectangleLinesEx, "Draw rectangle outline with extended parameters", nb::arg("rec"), nb::arg("line_thick"), nb::arg("color"));
    m.def("draw_rectangle_rounded", &DrawRectangleRounded, "Draw rectangle with rounded edges", nb::arg("rec"), nb::arg("roundness"), nb::arg("segments"), nb::arg("color"));
    m.def("draw_rectangle_rounded_lines", &DrawRectangleRoundedLines, "Draw rectangle lines with rounded edges", nb::arg("rec"), nb::arg("roundness"), nb::arg("segments"), nb::arg("color"));
    m.def("draw_rectangle_rounded_lines_ex", &DrawRectangleRoundedLinesEx, "Draw rectangle with rounded edges outline", nb::arg("rec"), nb::arg("roundness"), nb::arg("segments"), nb::arg("line_thick"), nb::arg("color"));    
    m.def("draw_triangle", &DrawTriangle, "Draw a color-filled triangle (vertex in counter-clockwise order!)", nb::arg("v1"), nb::arg("v2"), nb::arg("v3"), nb::arg("color"));
    m.def("draw_triangle_lines", &DrawTriangleLines, "Draw triangle outline (vertex in counter-clockwise order!)", nb::arg("v1"), nb::arg("v2"), nb::arg("v3"), nb::arg("color"));
    
    //m.def("draw_triangle_fan", &DrawTriangleFan, "Draw a triangle fan defined by points (first vertex is the center)", nb::arg("points"), nb::arg("point_count"), nb::arg("color"));
    //m.def("draw_triangle_strip", &DrawTriangleStrip, "Draw a triangle strip defined by points", nb::arg("points"), nb::arg("point_count"), nb::arg("color"));
    
    m.def("draw_triangle_fan", [](ArrayVector2 points, Color color) {
        DrawTriangleFan(reinterpret_cast<const Vector2*>(points.data()), points.shape(0), color);
    }, "Draw a triangle fan defined by points (first vertex is the center)", nb::arg("points"), nb::arg("color"));

    m.def("draw_triangle_strip", [](ArrayVector2 points, Color color) {
        DrawTriangleStrip(reinterpret_cast<const Vector2*>(points.data()), points.shape(0), color);
    }, "Draw a triangle strip defined by points", nb::arg("points"), nb::arg("color"));

    
    m.def("draw_poly", &DrawPoly, "Draw a regular polygon (Vector version)", nb::arg("center"), nb::arg("sides"), nb::arg("radius"), nb::arg("rotation"), nb::arg("color"));
    m.def("draw_poly_lines", &DrawPolyLines, "Draw a polygon outline of n sides", nb::arg("center"), nb::arg("sides"), nb::arg("radius"), nb::arg("rotation"), nb::arg("color"));
    m.def("draw_poly_lines_ex", &DrawPolyLinesEx, "Draw a polygon outline of n sides with extended parameters",nb::arg("center"), nb::arg("sides"), nb::arg("radius"), nb::arg("rotation"), nb::arg("line_thick"), nb::arg("color"));

    // Splines drawing functions
    m.def("draw_spline_linear", &DrawSplineLinear, "Draw spline: Linear, minimum 2 points", nb::arg("points"), nb::arg("point_count"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_basis", &DrawSplineBasis, "Draw spline: B-Spline, minimum 4 points", nb::arg("points"), nb::arg("point_count"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_catmull_rom", &DrawSplineCatmullRom, "Draw spline: Catmull-Rom, minimum 4 points", nb::arg("points"), nb::arg("point_count"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_bezier_quadratic", &DrawSplineBezierQuadratic, "Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]", nb::arg("points"), nb::arg("point_count"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_bezier_cubic", &DrawSplineBezierCubic, "Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]", nb::arg("points"), nb::arg("point_count"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_segment_linear", &DrawSplineSegmentLinear, "Draw spline segment: Linear, 2 points", nb::arg("p1"), nb::arg("p2"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_segment_basis", &DrawSplineSegmentBasis, "Draw spline segment: B-Spline, 4 points", nb::arg("p1"), nb::arg("p2"), nb::arg("p3"), nb::arg("p4"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_segment_catmull_rom", &DrawSplineSegmentCatmullRom, "Draw spline segment: Catmull-Rom, 4 points", nb::arg("p1"), nb::arg("p2"), nb::arg("p3"), nb::arg("p4"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_segment_bezier_quadratic", &DrawSplineSegmentBezierQuadratic, "Draw spline segment: Quadratic Bezier, 2 points, 1 control point", nb::arg("p1"), nb::arg("c2"), nb::arg("p3"), nb::arg("thick"), nb::arg("color"));
    m.def("draw_spline_segment_bezier_cubic", &DrawSplineSegmentBezierCubic, "Draw spline segment: Cubic Bezier, 2 points, 2 control points", nb::arg("p1"), nb::arg("c2"), nb::arg("c3"), nb::arg("p4"), nb::arg("thick"), nb::arg("color"));

}



