#include <iostream>
#include <nanobind/nanobind.h>
extern "C" {
#include <raylib.h>
}

// nanobind namespace
namespace nb = nanobind;



void export_rtexture(nb::module_& m)
{

    m.def("load_image", &LoadImage, "Load image from file into CPU memory (RAM)", nb::arg("filename"));
    m.def("load_image_raw", &LoadImageRaw, "Load image from RAW file data", nb::arg("filename"), nb::arg("width"), nb::arg("height"), nb::arg("format"), nb::arg("header_size"));
    m.def("load_image_anim", &LoadImageAnim, "Load image sequence from file", nb::arg("filename"), nb::arg("frames"));
    m.def("load_image_anim_from_memory", &LoadImageAnimFromMemory, "Load image sequence from memory buffer", nb::arg("file_type"), nb::arg("file_data"), nb::arg("data_size"), nb::arg("frames"));
    m.def("load_image_from_memory", &LoadImageFromMemory, "Load image from memory buffer", nb::arg("file_type"), nb::arg("file_data"), nb::arg("data_size"));
    m.def("load_image_from_texture", &LoadImageFromTexture, "Load image from GPU texture data", nb::arg("texture"));
    m.def("load_image_from_screen", &LoadImageFromScreen, "Load image from screen buffer");
    m.def("is_image_valid", &IsImageValid, "Check if an image is valid", nb::arg("image"));
    m.def("unload_image", &UnloadImage, "Unload image from CPU memory", nb::arg("image"));
    m.def("export_image", &ExportImage, "Export image data to file", nb::arg("image"), nb::arg("filename"));
    m.def("export_image_to_memory", &ExportImageToMemory, "Export image to memory buffer", nb::arg("image"), nb::arg("file_type"), nb::arg("file_size"));
    m.def("export_image_as_code", &ExportImageAsCode, "Export image as code file", nb::arg("image"), nb::arg("filename"));
    m.def("gen_image_color", &GenImageColor, "Generate image: plain color", nb::arg("width"), nb::arg("height"), nb::arg("color"));
    m.def("gen_image_gradient_linear", &GenImageGradientLinear, "Generate image: linear gradient", nb::arg("width"), nb::arg("height"), nb::arg("direction"), nb::arg("start"), nb::arg("end"));
    m.def("gen_image_gradient_radial", &GenImageGradientRadial, "Generate image: radial gradient", nb::arg("width"), nb::arg("height"), nb::arg("density"), nb::arg("inner"), nb::arg("outer"));
    m.def("gen_image_gradient_square", &GenImageGradientSquare, "Generate image: square gradient", nb::arg("width"), nb::arg("height"), nb::arg("density"), nb::arg("inner"), nb::arg("outer"));
    m.def("gen_image_checked", &GenImageChecked, "Generate image: checked", nb::arg("width"), nb::arg("height"), nb::arg("checksX"), nb::arg("checksY"), nb::arg("col1"), nb::arg("col2"));
    m.def("gen_image_white_noise", &GenImageWhiteNoise, "Generate image: white noise", nb::arg("width"), nb::arg("height"), nb::arg("factor"));
    m.def("gen_image_perlin_noise", &GenImagePerlinNoise, "Generate image: perlin noise", nb::arg("width"), nb::arg("height"), nb::arg("offsetX"), nb::arg("offsetY"), nb::arg("scale"));
    m.def("gen_image_cellular", &GenImageCellular, "Generate image: cellular", nb::arg("width"), nb::arg("height"), nb::arg("tileSize"));
    m.def("gen_image_text", &GenImageText, "Generate image: text", nb::arg("width"), nb::arg("height"), nb::arg("text"));
    m.def("image_copy", &ImageCopy, "Copy image", nb::arg("image"));
    m.def("image_from_image", &ImageFromImage, "Create image from another image", nb::arg("image"), nb::arg("rect"));
    m.def("image_from_channel", &ImageFromChannel, "Create image from a selected channel of another image", nb::arg("image"), nb::arg("selected_channel"));
    m.def("image_text", &ImageText, "Generate image from text", nb::arg("text"), nb::arg("font_size"), nb::arg("color"));
    m.def("image_text_ex", &ImageTextEx, "Generate image from text with additional parameters", nb::arg("text"), nb::arg("font_size"), nb::arg("color"), nb::arg("spacing"), nb::arg("tint"));
    m.def("image_format", &ImageFormat, "Convert image to another format", nb::arg("image"), nb::arg("format"));
    m.def("image_to_pot", &ImageToPOT, "Convert image to POT (power-of-two)", nb::arg("image"), nb::arg("fill"));
    m.def("image_crop", &ImageCrop, "Crop an image to a defined rectangle", nb::arg("image"), nb::arg("crop")); 
    m.def("image_alpha_crop", &ImageAlphaCrop, "Crop image depending on alpha value", nb::arg("image"), nb::arg("threshold"));
    m.def("image_alpha_clear", &ImageAlphaClear, "Clear alpha channel to desired color", nb::arg("image"), nb::arg("color"), nb::arg("threshold"));
    m.def("image_alpha_mask", &ImageAlphaMask, "Apply alpha mask to image", nb::arg("image"), nb::arg("alpha_mask"));
    m.def("image_alpha_premultiply", &ImageAlphaPremultiply, "Premultiply alpha channel", nb::arg("image"));
    m.def("image_blur_gaussian", &ImageBlurGaussian, "Apply Gaussian blur to an image", nb::arg("image"), nb::arg("blur_size"));
    m.def("image_kernel_convolution", &ImageKernelConvolution, "Apply custom square convolution kernel to image", nb::arg("image"), nb::arg("kernel"), nb::arg("kernel_size"));
    m.def("image_resize", &ImageResize, "Resize image (Bicubic scaling algorithm)", nb::arg("image"), nb::arg("new_width"), nb::arg("new_height"));
    m.def("image_resize_nn", &ImageResizeNN, "Resize image (Nearest-Neighbor scaling algorithm)", nb::arg("image"), nb::arg("new_width"), nb::arg("new_height"));
    m.def("image_resize_canvas", &ImageResizeCanvas, "Resize canvas and fill with color", nb::arg("image"), nb::arg("new_width"), nb::arg("new_height"), nb::arg("offset_x"), nb::arg("offset_y"), nb::arg("fill"));
    m.def("image_mipmaps", &ImageMipmaps, "Compute all mipmap levels for a provided image", nb::arg("image"));
    m.def("image_dither", &ImageDither, "Dither image data to 16bpp or lower", nb::arg("image"), nb::arg("r_bpp"), nb::arg("g_bpp"), nb::arg("b_bpp"), nb::arg("a_bpp"));
    m.def("image_flip_vertical", &ImageFlipVertical, "Flip image vertically", nb::arg("image"));
    m.def("image_flip_horizontal", &ImageFlipHorizontal, "Flip image horizontally", nb::arg("image"));
    m.def("image_rotate", &ImageRotate, "Rotate image by input angle in degrees", nb::arg("image"), nb::arg("degrees"));
    m.def("image_rotate_cw", &ImageRotateCW, "Rotate image clockwise 90 degrees", nb::arg("image"));
    m.def("image_rotate_ccw", &ImageRotateCCW, "Rotate image counter-clockwise 90 degrees", nb::arg("image"));
    m.def("image_color_tint", &ImageColorTint, "Modify image color: tint", nb::arg("image"), nb::arg("color"));
    m.def("image_color_invert", &ImageColorInvert, "Modify image color: invert", nb::arg("image"));
    m.def("image_color_grayscale", &ImageColorGrayscale, "Modify image color: grayscale", nb::arg("image"));
    m.def("image_color_contrast", &ImageColorContrast, "Modify image color: contrast (-100 to 100)", nb::arg("image"), nb::arg("contrast"));
    m.def("image_color_brightness", &ImageColorBrightness, "Modify image color: brightness (-255 to 255)", nb::arg("image"), nb::arg("brightness"));
    m.def("image_color_replace", &ImageColorReplace, "Modify image color: replace color", nb::arg("image"), nb::arg("color"), nb::arg("replace"));
    m.def("load_image_colors", &LoadImageColors, "Load color data from image as a Color array (RGBA - 32bit)", nb::arg("image"));
    m.def("load_image_palette", &LoadImagePalette, "Load colors palette from image as a Color array (RGBA - 32bit)", nb::arg("image"), nb::arg("maxPaletteSize"), nb::arg("colorCount"));
    m.def("unload_image_colors", &UnloadImageColors, "Unload color data loaded with LoadImageColors()", nb::arg("colors"));
    m.def("unload_image_palette", &UnloadImagePalette, "Unload colors palette loaded with LoadImagePalette()", nb::arg("colors"));
    m.def("get_image_alpha_border", &GetImageAlphaBorder, "Get image alpha border rectangle", nb::arg("image"), nb::arg("threshold"));
    m.def("get_image_color", &GetImageColor, "Get image pixel color at (x, y) position", nb::arg("image"), nb::arg("x"), nb::arg("y"));

    m.def("image_clear_background", &ImageClearBackground, "Clear image background with given color", nb::arg("image"), nb::arg("color"));
    m.def("image_draw_pixel", &ImageDrawPixel, "Draw pixel within an image", nb::arg("image"), nb::arg("posX"), nb::arg("posY"), nb::arg("color"));
    m.def("image_draw_pixel_v", &ImageDrawPixelV, "Draw pixel within an image (Vector version)", nb::arg("image"), nb::arg("position"), nb::arg("color"));
    m.def("image_draw_line", &ImageDrawLine, "Draw line within an image", nb::arg("image"), nb::arg("startPosX"), nb::arg("startPosY"), nb::arg("endPosX"), nb::arg("endPosY"), nb::arg("color"));
    m.def("image_draw_line_v", &ImageDrawLineV, "Draw line within an image (Vector version)", nb::arg("image"), nb::arg("start"), nb::arg("end"), nb::arg("color"));
    m.def("image_draw_line_ex", &ImageDrawLineEx, "Draw a line defining thickness within an image", nb::arg("image"), nb::arg("start"), nb::arg("end"), nb::arg("thick"), nb::arg("color"));
    m.def("image_draw_circle", &ImageDrawCircle, "Draw a filled circle within an image", nb::arg("image"), nb::arg("centerX"), nb::arg("centerY"), nb::arg("radius"), nb::arg("color"));
    m.def("image_draw_circle_v", &ImageDrawCircleV, "Draw a filled circle within an image (Vector version)", nb::arg("image"), nb::arg("center"), nb::arg("radius"), nb::arg("color"));
    m.def("image_draw_circle_lines", &ImageDrawCircleLines, "Draw circle outline within an image", nb::arg("image"), nb::arg("centerX"), nb::arg("centerY"), nb::arg("radius"), nb::arg("color"));
    m.def("image_draw_circle_lines_v", &ImageDrawCircleLinesV, "Draw circle outline within an image (Vector version)", nb::arg("image"), nb::arg("center"), nb::arg("radius"), nb::arg("color"));
    m.def("image_draw_rectangle", &ImageDrawRectangle, "Draw rectangle within an image", nb::arg("image"), nb::arg("posX"), nb::arg("posY"), nb::arg("width"), nb::arg("height"), nb::arg("color"));
    m.def("image_draw_rectangle_v", &ImageDrawRectangleV, "Draw rectangle within an image (Vector version)", nb::arg("image"), nb::arg("position"), nb::arg("size"), nb::arg("color"));
    m.def("image_draw_rectangle_rec", &ImageDrawRectangleRec, "Draw rectangle within an image", nb::arg("image"), nb::arg("rec"), nb::arg("color"));
    m.def("image_draw_rectangle_lines", &ImageDrawRectangleLines, "Draw rectangle outline within an image", nb::arg("image"), nb::arg("rec"), nb::arg("thick"), nb::arg("color"));
    m.def("image_draw_triangle", &ImageDrawTriangle, "Draw triangle within an image", nb::arg("image"), nb::arg("v1"), nb::arg("v2"), nb::arg("v3"), nb::arg("color"));
    m.def("image_draw_triangle_ex", &ImageDrawTriangleEx, "Draw triangle with interpolated colors within an image", nb::arg("image"), nb::arg("v1"), nb::arg("v2"), nb::arg("v3"), nb::arg("c1"), nb::arg("c2"), nb::arg("c3"));
    m.def("image_draw_triangle_lines", &ImageDrawTriangleLines, "Draw triangle outline within an image", nb::arg("image"), nb::arg("v1"), nb::arg("v2"), nb::arg("v3"), nb::arg("color"));
    m.def("image_draw_triangle_fan", &ImageDrawTriangleFan, "Draw a triangle fan defined by points within an image", nb::arg("image"), nb::arg("points"), nb::arg("pointCount"), nb::arg("color"));
    m.def("image_draw_triangle_strip", &ImageDrawTriangleStrip, "Draw a triangle strip defined by points within an image", nb::arg("image"), nb::arg("points"), nb::arg("pointCount"), nb::arg("color"));
    m.def("image_draw", &ImageDraw, "Draw a source image within a destination image (tint applied to source)", nb::arg("image"), nb::arg("src"), nb::arg("srcRec"), nb::arg("dstRec"), nb::arg("tint"));
    m.def("image_draw_text", &ImageDrawText, "Draw text (using default font) within an image (destination)", nb::arg("image"), nb::arg("text"), nb::arg("posX"), nb::arg("posY"), nb::arg("fontSize"), nb::arg("color"));
    m.def("image_draw_text_ex", &ImageDrawTextEx, "Draw text (custom sprite font) within an image (destination)", nb::arg("image"), nb::arg("font"), nb::arg("text"), nb::arg("position"), nb::arg("fontSize"), nb::arg("spacing"), nb::arg("tint"));

    // // Texture loading functions
    m.def("load_texture", &LoadTexture, "Load texture from file into GPU memory (VRAM)", nb::arg("filename"));
    m.def("load_texture_from_image", &LoadTextureFromImage, "Load texture from image data", nb::arg("image"));
    m.def("load_texture_cubemap", &LoadTextureCubemap, "Load cubemap from image, multiple image cubemap layouts supported", nb::arg("image"), nb::arg("layout"));
    m.def("load_render_texture", &LoadRenderTexture, "Load texture for rendering (framebuffer)", nb::arg("width"), nb::arg("height"));
    m.def("is_texture_valid", &IsTextureValid, "Check if a texture is valid (loaded in GPU)", nb::arg("texture"));
    m.def("unload_texture", &UnloadTexture, "Unload texture from GPU memory (VRAM)", nb::arg("texture"));
    m.def("is_render_texture_valid", &IsRenderTextureValid, "Check if a render texture is valid (loaded in GPU)", nb::arg("target"));
    m.def("unload_render_texture", &UnloadRenderTexture, "Unload render texture from GPU memory (VRAM)", nb::arg("target"));
    m.def("update_texture", &UpdateTexture, "Update GPU texture with new data", nb::arg("texture"), nb::arg("pixels"));
    m.def("update_texture_rec", &UpdateTextureRec, "Update GPU texture rectangle with new data", nb::arg("texture"), nb::arg("rec"), nb::arg("pixels"));

    // // Texture configuration functions
    m.def("gen_texture_mipmaps", &GenTextureMipmaps, "Generate GPU mipmaps for a texture", nb::arg("texture"));
    m.def("set_texture_filter", &SetTextureFilter, "Set texture scaling filter mode", nb::arg("texture"), nb::arg("filter"));
    m.def("set_texture_wrap", &SetTextureWrap, "Set texture wrapping mode", nb::arg("texture"), nb::arg("wrap"));

    // // Texture drawing functions
    m.def("draw_texture", &DrawTexture, "Draw a Texture2D", nb::arg("texture"), nb::arg("posX"), nb::arg("posY"), nb::arg("tint"));
    m.def("draw_texture_v", &DrawTextureV, "Draw a Texture2D with position defined as Vector2", nb::arg("texture"), nb::arg("position"), nb::arg("tint"));
    m.def("draw_texture_ex", &DrawTextureEx, "Draw a Texture2D with extended parameters", nb::arg("texture"), nb::arg("position"), nb::arg("rotation"), nb::arg("scale"), nb::arg("tint"));
    m.def("draw_texture_rec", &DrawTextureRec, "Draw a part of a texture defined by a rectangle", nb::arg("texture"), nb::arg("source"), nb::arg("position"), nb::arg("tint"));
    m.def("draw_texture_pro", &DrawTexturePro, "Draw a part of a texture defined by a rectangle with 'pro' parameters", nb::arg("texture"), nb::arg("source"), nb::arg("dest"), nb::arg("origin"), nb::arg("rotation"), nb::arg("tint"));
    m.def("draw_texture_n_patch", &DrawTextureNPatch, "Draws a texture (or part of it) that stretches or shrinks nicely", nb::arg("texture"), nb::arg("nPatchInfo"), nb::arg("dest"), nb::arg("origin"), nb::arg("rotation"), nb::arg("tint"));

    // // Color/pixel related functions
    m.def("color_is_equal", &ColorIsEqual, "Check if two colors are equal", nb::arg("col1"), nb::arg("col2"));
    m.def("fade", &Fade, "Get color with alpha applied", nb::arg("color"), nb::arg("alpha"));
    m.def("color_to_int", &ColorToInt, "Get hexadecimal value for a Color", nb::arg("color"));
    m.def("color_normalize", &ColorNormalize, "Get Color normalized as float [0..1]", nb::arg("color"));
    m.def("color_from_normalized", &ColorFromNormalized, "Get Color from normalized values [0..1]", nb::arg("normalized"));
    m.def("color_to_hsv", &ColorToHSV, "Get HSV values for a Color", nb::arg("color"));
    m.def("color_from_hsv", &ColorFromHSV, "Get a Color from HSV values", nb::arg("hue"), nb::arg("saturation"), nb::arg("value"));
    m.def("color_tint", &ColorTint, "Get color multiplied with another color", nb::arg("color"), nb::arg("tint"));
    m.def("color_brightness", &ColorBrightness, "Get color with brightness correction", nb::arg("color"), nb::arg("factor"));
    m.def("color_contrast", &ColorContrast, "Get color with contrast correction", nb::arg("color"), nb::arg("contrast"));
    m.def("color_alpha", &ColorAlpha, "Get color with alpha applied", nb::arg("color"), nb::arg("alpha"));
    m.def("color_alpha_blend", &ColorAlphaBlend, "Get src alpha-blended into dst color with tint", nb::arg("dst"), nb::arg("src"), nb::arg("tint"));
    m.def("color_lerp", &ColorLerp, "Get color lerp interpolation between two colors", nb::arg("color1"), nb::arg("color2"), nb::arg("factor"));
    m.def("get_color", &GetColor, "Get Color structure from hexadecimal value", nb::arg("hex_value"));
    m.def("get_pixel_color", &GetPixelColor, "Get Color from a source pixel pointer of certain format", nb::arg("srcPtr"), nb::arg("format"));
    m.def("set_pixel_color", &SetPixelColor, "Set color formatted into destination pixel pointer", nb::arg("dstPtr"), nb::arg("color"), nb::arg("format"));
    m.def("get_pixel_data_size", &GetPixelDataSize, "Get pixel data size in bytes for certain format", nb::arg("width"), nb::arg("height"), nb::arg("format"));
}