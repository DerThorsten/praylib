
//     // VR stereo config functions for VR simulator
//     VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device);     // Load VR stereo config for VR simulator device parameters
//     void UnloadVrStereoConfig(VrStereoConfig config);           // Unload VR stereo config

//    

//     // Custom frame control functions
//     // NOTE: Those functions are intended for advanced users that want full control over the frame processing
//     // By default EndDrawing() does this job: draws everything + SwapScreenBuffer() + manage frame timing + PollInputEvents()
//     // To avoid that behaviour and control frame processes manually, enable in config.h: SUPPORT_CUSTOM_FRAME_CONTROL
//     void SwapScreenBuffer(void);                                // Swap back buffer with front buffer (screen drawing)
//     void PollInputEvents(void);                                 // Register all input events
//     void WaitTime(double seconds);                              // Wait for some time (halt program execution)

//     // Random values generation functions
//     void SetRandomSeed(unsigned int seed);                      // Set the seed for the random number generator
//     int GetRandomValue(int min, int max);                       // Get a random value between min and max (both included)
//     int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
//     void UnloadRandomSequence(int *sequence);                   // Unload random values sequence

//     // Misc. functions
//     void TakeScreenshot(const char *fileName);                  // Takes a screenshot of current screen (filename extension defines format)
//     void SetConfigFlags(unsigned int flags);                    // Setup init configuration flags (view FLAGS)
//     void OpenURL(const char *url);                              // Open URL with default system browser (if available)

//     // NOTE: Following functions implemented in module [utils]
//     //------------------------------------------------------------------
//     void TraceLog(int logLevel, const char *text, ...);         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
//     void SetTraceLogLevel(int logLevel);                        // Set the current threshold (minimum) log level
//     void *MemAlloc(unsigned int size);                          // Internal memory allocator
//     void *MemRealloc(void *ptr, unsigned int size);             // Internal memory reallocator
//     void MemFree(void *ptr);                                    // Internal memory free

//     // Set custom callbacks
//     // WARNING: Callbacks setup is intended for advanced users
//     void SetTraceLogCallback(TraceLogCallback callback);         // Set custom trace log
//     void SetLoadFileDataCallback(LoadFileDataCallback callback); // Set custom file binary data loader
//     void SetSaveFileDataCallback(SaveFileDataCallback callback); // Set custom file binary data saver
//     void SetLoadFileTextCallback(LoadFileTextCallback callback); // Set custom file text data loader
//     void SetSaveFileTextCallback(SaveFileTextCallback callback); // Set custom file text data saver

//     // Files management functions
//     unsigned char *LoadFileData(const char *fileName, int *dataSize); // Load file data as byte array (read)
//     void UnloadFileData(unsigned char *data);                   // Unload file data allocated by LoadFileData()
//     bool SaveFileData(const char *fileName, void *data, int dataSize); // Save data to file from byte array (write), returns true on success
//     bool ExportDataAsCode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
//     char *LoadFileText(const char *fileName);                   // Load text data from file (read), returns a '\0' terminated string
//     void UnloadFileText(char *text);                            // Unload file text data allocated by LoadFileText()
//     bool SaveFileText(const char *fileName, char *text);        // Save text data to file (write), string must be '\0' terminated, returns true on success
//     //------------------------------------------------------------------

//     // File system functions
//     bool FileExists(const char *fileName);                      // Check if file exists
//     bool DirectoryExists(const char *dirPath);                  // Check if a directory path exists
//     bool IsFileExtension(const char *fileName, const char *ext); // Check file extension (including point: .png, .wav)
//     int GetFileLength(const char *fileName);                    // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
//     const char *GetFileExtension(const char *fileName);         // Get pointer to extension for a filename string (includes dot: '.png')
//     const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
//     const char *GetFileNameWithoutExt(const char *filePath);    // Get filename string without extension (uses static string)
//     const char *GetDirectoryPath(const char *filePath);         // Get full path for a given fileName with path (uses static string)
//     const char *GetPrevDirectoryPath(const char *dirPath);      // Get previous directory path for a given path (uses static string)
//     const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
//     const char *GetApplicationDirectory(void);                  // Get the directory of the running application (uses static string)
//     int MakeDirectory(const char *dirPath);                     // Create directories (including full path requested), returns 0 on success
//     bool ChangeDirectory(const char *dir);                      // Change working directory, return true on success
//     bool IsPathFile(const char *path);                          // Check if a given path is a file or a directory
//     bool IsFileNameValid(const char *fileName);                 // Check if fileName is valid for the platform/OS
//     FilePathList LoadDirectoryFiles(const char *dirPath);       // Load directory filepaths
//     FilePathList LoadDirectoryFilesEx(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
//     void UnloadDirectoryFiles(FilePathList files);              // Unload filepaths
//     bool IsFileDropped(void);                                   // Check if a file has been dropped into window
//     FilePathList LoadDroppedFiles(void);                        // Load dropped filepaths
//     void UnloadDroppedFiles(FilePathList files);                // Unload dropped filepaths
//     long GetFileModTime(const char *fileName);                  // Get file modification time (last write time)

//     // Compression/Encoding functionality
//     unsigned char *CompressData(const unsigned char *data, int dataSize, int *compDataSize);        // Compress data (DEFLATE algorithm), memory must be MemFree()
//     unsigned char *DecompressData(const unsigned char *compData, int compDataSize, int *dataSize);  // Decompress data (DEFLATE algorithm), memory must be MemFree()
//     char *EncodeDataBase64(const unsigned char *data, int dataSize, int *outputSize);               // Encode data to Base64 string, memory must be MemFree()
//     unsigned char *DecodeDataBase64(const unsigned char *data, int *outputSize);                    // Decode Base64 string data, memory must be MemFree()
//     unsigned int ComputeCRC32(unsigned char *data, int dataSize);     // Compute CRC32 hash code
//     unsigned int *ComputeMD5(unsigned char *data, int dataSize);      // Compute MD5 hash code, returns static int[4] (16 bytes)
//     unsigned int *ComputeSHA1(unsigned char *data, int dataSize);      // Compute SHA1 hash code, returns static int[5] (20 bytes)


//     // Automation events functionality
//     AutomationEventList LoadAutomationEventList(const char *fileName);                // Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
//     void UnloadAutomationEventList(AutomationEventList list);                         // Unload automation events list from file
//     bool ExportAutomationEventList(AutomationEventList list, const char *fileName);   // Export automation events list as text file
//     void SetAutomationEventList(AutomationEventList *list);                           // Set automation event list to record to
//     void SetAutomationEventBaseFrame(int frame);                                      // Set automation event internal base frame to start recording
//     void StartAutomationEventRecording(void);                                         // Start recording automation events (AutomationEventList must be set)
//     void StopAutomationEventRecording(void);                                          // Stop recording automation events
//     void PlayAutomationEvent(AutomationEvent event);                                  // Play a recorded automation event



//     //------------------------------------------------------------------------------------
//     // Camera System Functions (Module: rcamera)
//     //------------------------------------------------------------------------------------
//     void UpdateCamera(Camera *camera, int mode);      // Update camera position for selected mode
//     void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation







#include <iostream>

#include <nanobind/ndarray.h>
#include <nanobind/nanobind.h>


// make it extern C
extern "C" {
#include <raylib.h>
}

// nanobind namespace
namespace nb = nanobind;


void export_window(nb::module_& m)
{
    // Window-related functions
    m.def("init_window", &InitWindow, "Initialize window and OpenGL context", nb::arg("width"), nb::arg("height"), nb::arg("title"));
    m.def("close_window", &CloseWindow, "Close window and unload OpenGL context");
    m.def("window_should_close", &WindowShouldClose, "Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)");
    m.def("is_window_ready", &IsWindowReady, "Check if window has been initialized successfully");
    m.def("is_window_fullscreen", &IsWindowFullscreen, "Check if window is currently fullscreen");
    m.def("is_window_hidden", &IsWindowHidden, "Check if window is currently hidden");
    m.def("is_window_minimized", &IsWindowMinimized, "Check if window is currently minimized");
    m.def("is_window_maximized", &IsWindowMaximized, "Check if window is currently maximized");
    m.def("is_window_focused", &IsWindowFocused, "Check if window is currently focused");
    m.def("is_window_resized", &IsWindowResized, "Check if window has been resized last frame");
    m.def("is_window_state", &IsWindowState, "Check if one specific window flag is enabled", nb::arg("flag"));
    m.def("set_window_state", &SetWindowState, "Set window configuration state using flags", nb::arg("flags"));
    m.def("clear_window_state", &ClearWindowState, "Clear window configuration state flags", nb::arg("flags"));
    m.def("toggle_fullscreen", &ToggleFullscreen, "Toggle window state: fullscreen/windowed, resizes monitor to match window resolution");  
    m.def("toggle_borderless_windowed", &ToggleBorderlessWindowed, "Toggle window state: borderless windowed, resizes window to match monitor resolution");
    m.def("maximize_window", &MaximizeWindow, "Set window state: maximized, if resizable");
    m.def("minimize_window", &MinimizeWindow, "Set window state: minimized, if resizable");
    m.def("restore_window", &RestoreWindow, "Set window state: not minimized/maximized");
    m.def("set_window_icon", &SetWindowIcon, "Set icon for window (single image, RGBA 32bit)", nb::arg("image"));
    m.def("set_window_icons", &SetWindowIcons, "Set icon for window (multiple images, RGBA 32bit)", nb::arg("images"), nb::arg("count"));
    m.def("set_window_title", &SetWindowTitle, "Set title for window", nb::arg("title"));
    m.def("set_window_position", &SetWindowPosition, "Set window position on screen", nb::arg("x"), nb::arg("y"));
    m.def("set_window_monitor", &SetWindowMonitor, "Set monitor for the current window", nb::arg("monitor"));
    m.def("set_window_min_size", &SetWindowMinSize, "Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)", nb::arg("width"), nb::arg("height"));
    m.def("set_window_max_size", &SetWindowMaxSize, "Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)", nb::arg("width"), nb::arg("height"));
    m.def("set_window_size", &SetWindowSize, "Set window dimensions", nb::arg("width"), nb::arg("height"));
    m.def("set_window_opacity", &SetWindowOpacity, "Set window opacity [0.0f..1.0f]", nb::arg("opacity"));
    m.def("set_window_focused", &SetWindowFocused, "Set window focused");
    m.def("get_window_handle", &GetWindowHandle, "Get native window handle");
    m.def("get_screen_width", &GetScreenWidth, "Get current screen width");
    m.def("get_screen_height", &GetScreenHeight, "Get current screen height");
    m.def("get_render_width", &GetRenderWidth, "Get current render width (it considers HiDPI)");
    m.def("get_render_height", &GetRenderHeight, "Get current render height (it considers HiDPI)");
    m.def("get_monitor_count", &GetMonitorCount, "Get number of connected monitors");
    m.def("get_current_monitor", &GetCurrentMonitor, "Get current monitor where window is placed");
    m.def("get_monitor_position", &GetMonitorPosition, "Get specified monitor position", nb::arg("monitor"));
    m.def("get_monitor_width", &GetMonitorWidth, "Get specified monitor width (current video mode used by monitor)", nb::arg("monitor"));
    m.def("get_monitor_height", &GetMonitorHeight, "Get specified monitor height (current video mode used by monitor)", nb::arg("monitor"));
    m.def("get_monitor_physical_width", &GetMonitorPhysicalWidth, "Get specified monitor physical width in millimetres", nb::arg("monitor"));
    m.def("get_monitor_physical_height", &GetMonitorPhysicalHeight, "Get specified monitor physical height in millimetres", nb::arg("monitor"));
    m.def("get_monitor_refresh_rate", &GetMonitorRefreshRate, "Get specified monitor refresh rate", nb::arg("monitor"));
    m.def("get_window_position", &GetWindowPosition, "Get window position XY on monitor");
    m.def("get_window_scale_dpi", &GetWindowScaleDPI, "Get window scale DPI factor");
    m.def("get_monitor_name", &GetMonitorName, "Get the human-readable, UTF-8 encoded name of the specified monitor", nb::arg("monitor"));
    m.def("set_clipboard_text", &SetClipboardText, "Set clipboard text content", nb::arg("text"));
    m.def("get_clipboard_text", &GetClipboardText, "Get clipboard text content");
    m.def("get_clipboard_image", &GetClipboardImage, "Get clipboard image");
    m.def("enable_event_waiting", &EnableEventWaiting, "Enable waiting for events on EndDrawing(), no automatic event polling");
    m.def("disable_event_waiting", &DisableEventWaiting, "Disable waiting for events on EndDrawing(), automatic events polling");
}

// cursor management functions
void export_cursor(nb::module_& m)
{
    m.def("show_cursor", &ShowCursor, "Shows cursor");
    m.def("hide_cursor", &HideCursor, "Hides cursor");
    m.def("is_cursor_hidden", &IsCursorHidden, "Check if cursor is not visible");
    m.def("enable_cursor", &EnableCursor, "Enables cursor (unlock cursor)");
    m.def("disable_cursor", &DisableCursor, "Disables cursor (lock cursor)");
    m.def("is_cursor_on_screen", &IsCursorOnScreen, "Check if cursor is on the screen");
}

// export drawing functions
void export_drawing(nb::module_& m)
{
    m.def("clear_background", &ClearBackground, "Clear the background with a color", nb::arg("color"));
    m.def("begin_drawing", &BeginDrawing, "Begin drawing to the screen");
    m.def("end_drawing", &EndDrawing, "End drawing to the screen");
    m.def("begin_mode_2d", &BeginMode2D, "Begin 2D mode with camera", nb::arg("camera"));
    m.def("end_mode_2d", &EndMode2D, "End 2D mode with camera");
    m.def("begin_mode_3d", &BeginMode3D, "Begin 3D mode with camera", nb::arg("camera"));
    m.def("end_mode_3d", &EndMode3D, "End 3D mode with camera");
    m.def("begin_texture_mode", &BeginTextureMode, "Begin drawing to a render texture", nb::arg("target"));
    m.def("end_texture_mode", &EndTextureMode, "End drawing to a render texture");
    m.def("begin_shader_mode", &BeginShaderMode, "Begin custom shader mode", nb::arg("shader"));
    m.def("end_shader_mode", &EndShaderMode, "End custom shader mode");
    m.def("begin_blend_mode", &BeginBlendMode, "Begin blending mode", nb::arg("mode"));
    m.def("end_blend_mode", &EndBlendMode, "End blending mode");
    m.def("begin_scissor_mode", &BeginScissorMode, "Begin scissor mode", nb::arg("x"), nb::arg("y"), nb::arg("width"), nb::arg("height"));
    m.def("end_scissor_mode", &EndScissorMode, "End scissor mode");
    m.def("begin_vr_stereo_mode", &BeginVrStereoMode, "Begin stereo rendering with VR device", nb::arg("config"));
    m.def("end_vr_stereo_mode", &EndVrStereoMode, "End stereo rendering with VR device");

}

void export_input_handling(nb::module_& m)
{
    m.def("is_key_pressed", &IsKeyPressed, "Check if a key has been pressed once", nb::arg("key"));
    m.def("is_key_pressed_repeat", &IsKeyPressedRepeat, "Check if a key has been pressed again", nb::arg("key"));
    m.def("is_key_down", &IsKeyDown, "Check if a key is being pressed", nb::arg("key"));
    m.def("is_key_released", &IsKeyReleased, "Check if a key has been released once", nb::arg("key"));
    m.def("is_key_up", &IsKeyUp, "Check if a key is NOT being pressed", nb::arg("key"));
    m.def("get_key_pressed", &GetKeyPressed, "Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty");
    m.def("get_char_pressed", &GetCharPressed, "Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty");
    m.def("set_exit_key", &SetExitKey, "Set a custom key to exit program (default is ESC)", nb::arg("key"));

    m.def("is_gamepad_available", &IsGamepadAvailable, "Check if a gamepad is available", nb::arg("gamepad"));
    m.def("get_gamepad_name", &GetGamepadName, "Get gamepad internal name id", nb::arg("gamepad"));
    m.def("is_gamepad_button_pressed", &IsGamepadButtonPressed, "Check if a gamepad button has been pressed once", nb::arg("gamepad"), nb::arg("button"));
    m.def("is_gamepad_button_down", &IsGamepadButtonDown, "Check if a gamepad button is being pressed", nb::arg("gamepad"), nb::arg("button"));
    m.def("is_gamepad_button_released", &IsGamepadButtonReleased, "Check if a gamepad button hasq   been released once", nb::arg("gamepad"), nb::arg("button"));
    m.def("is_gamepad_button_up", &IsGamepadButtonUp, "Check if a gamepad button is NOT being pressed", nb::arg("gamepad"), nb::arg("button"));
    m.def("get_gamepad_button_pressed", &GetGamepadButtonPressed, "Get the last gamepad button pressed");
    m.def("get_gamepad_axis_count", &GetGamepadAxisCount, "Get gamepad axis count for a gamepad", nb::arg("gamepad"));
    m.def("get_gamepad_axis_movement", &GetGamepadAxisMovement, "Get axis movement value for a gamepad axis", nb::arg("gamepad"), nb::arg("axis"));
    m.def("set_gamepad_mappings", &SetGamepadMappings, "Set internal gamepad mappings (SDL_GameControllerDB)", nb::arg("mappings"));
    m.def("set_gamepad_vibration", &SetGamepadVibration, "Set gamepad vibration for both motors (duration in seconds)", nb::arg("gamepad"), nb::arg("leftMotor"), nb::arg("rightMotor"), nb::arg("duration"));

    m.def("is_mouse_button_pressed", &IsMouseButtonPressed, "Check if a mouse button has been pressed once", nb::arg("button"));
    m.def("is_mouse_button_down", &IsMouseButtonDown, "Check if a mouse button is being pressed", nb::arg("button"));
    m.def("is_mouse_button_released", &IsMouseButtonReleased, "Check if a mouse button has been released once", nb::arg("button"));
    m.def("is_mouse_button_up", &IsMouseButtonUp, "Check if a mouse button is NOT being pressed", nb::arg("button"));
    m.def("get_mouse_x", &GetMouseX, "Get mouse position X");
    m.def("get_mouse_y", &GetMouseY, "Get mouse position Y");
    m.def("get_mouse_position", &GetMousePosition, "Get mouse position XY");
    m.def("get_mouse_delta", &GetMouseDelta, "Get mouse delta between frames");
    m.def("set_mouse_position", &SetMousePosition, "Set mouse position XY", nb::arg("x"), nb::arg("y"));
    m.def("set_mouse_offset", &SetMouseOffset, "Set mouse offset", nb::arg("offsetX"), nb::arg("offsetY"));
    m.def("set_mouse_scale", &SetMouseScale, "Set mouse scaling", nb::arg("scaleX"), nb::arg("scaleY"));
    m.def("get_mouse_wheel_move", &GetMouseWheelMove, "Get mouse wheel movement for X or Y, whichever is larger");
    m.def("get_mouse_wheel_move_v", &GetMouseWheelMoveV, "Get mouse wheel movement for both X and Y");
    m.def("set_mouse_cursor", &SetMouseCursor, "Set mouse cursor", nb::arg("cursor"));

    m.def("get_touch_x", &GetTouchX, "Get touch position X for touch point 0 (relative to screen size)");
    m.def("get_touch_y", &GetTouchY, "Get touch position Y for touch point 0 (relative to screen size)");
    m.def("get_touch_position", &GetTouchPosition, "Get touch position XY for a touch point index (relative to screen size)", nb::arg("index"));
    m.def("get_touch_point_id", &GetTouchPointId, "Get touch point identifier for given index", nb::arg("index"));
    m.def("get_touch_point_count", &GetTouchPointCount, "Get number of touch points");  

    m.def("set_gestures_enabled", &SetGesturesEnabled, "Enable a set of gestures using flags", nb::arg("flags"));
    m.def("is_gesture_detected", &IsGestureDetected, "Check if a gesture have been detected", nb::arg("gesture"));
    m.def("get_gesture_detected", &GetGestureDetected, "Get latest detected gesture");
    m.def("get_gesture_hold_duration", &GetGestureHoldDuration, "Get gesture hold time in seconds");
    m.def("get_gesture_drag_vector", &GetGestureDragVector, "Get gesture drag vector");
    m.def("get_gesture_drag_angle", &GetGestureDragAngle, "Get gesture drag angle");
    m.def("get_gesture_pinch_vector", &GetGesturePinchVector, "Get gesture pinch delta");
    m.def("get_gesture_pinch_angle", &GetGesturePinchAngle, "Get gesture pinch angle");     

}
void export_timing(nb::module_& m)
{
    m.def("set_target_fps", &SetTargetFPS, "Set target FPS (maximum)", nb::arg("fps"));
    m.def("get_frame_time", &GetFrameTime, "Get time in seconds for last frame drawn (delta time)");
    m.def("get_time", &GetTime, "Get elapsed time in seconds since InitWindow");
    m.def("get_fps", &GetFPS , "Get current FPS");
}


void export_screen_space(nb::module_& m)
{
    m.def("get_mouse_ray", &GetMouseRay, "Get mouse ray (from mouse position)", nb::arg("mouse_position"), nb::arg("camera"));
    m.def("get_screen_to_world_ray", &GetScreenToWorldRay, "Get screen to world ray", nb::arg("position"), nb::arg("camera"));
    m.def("get_screen_to_world_ray_ex", &GetScreenToWorldRayEx, "Get screen to world ray (with viewport)", nb::arg("position"), nb::arg("camera"), nb::arg("width"), nb::arg("height"));
    m.def("get_world_to_screen", &GetWorldToScreen, "Get world to screen position", nb::arg("position"), nb::arg("camera"));
    m.def("get_world_to_screen_ex", &GetWorldToScreenEx, "Get world to screen position (with viewport)", nb::arg("position"), nb::arg("camera"), nb::arg("width"), nb::arg("height"));
    m.def("get_world_to_screen_2d", &GetWorldToScreen2D, "Get world to screen position (2D)", nb::arg("position"), nb::arg("camera"));
    m.def("get_screen_to_world_2d", &GetScreenToWorld2D, "Get screen to world position (2D)", nb::arg("position"), nb::arg("camera"));
    m.def("get_camera_matrix", &GetCameraMatrix, "Get camera matrix", nb::arg("camera"));
    m.def("get_camera_matrix_2d", &GetCameraMatrix2D, "Get camera 2D matrix", nb::arg("camera"));

}

void export_text_drawing(nb::module_& m)
{

    m.def("draw_fps", &DrawFPS, "Draw current FPS", nb::arg("pos_x"), nb::arg("pos_y"));
    m.def("draw_text", &DrawText, "Draw text (using default font)", nb::arg("text"), nb::arg("pos_x"), nb::arg("pos_y"), nb::arg("font_size"), nb::arg("color"));
    m.def("draw_text_ex", &DrawTextEx, "Draw text using font and additional parameters", nb::arg("font"), nb::arg("text"), nb::arg("position"), nb::arg("font_size"), nb::arg("spacing"), nb::arg("tint"));
    m.def("draw_text_pro", &DrawTextPro, "Draw text using Font and pro parameters (rotation)", nb::arg("font"), nb::arg("text"), nb::arg("position"), nb::arg("origin"), nb::arg("rotation"), nb::arg("font_size"), nb::arg("spacing"), nb::arg("tint"));
    m.def("draw_text_codepoint", &DrawTextCodepoint, "Draw one character (codepoint)", nb::arg("font"), nb::arg("codepoint"), nb::arg("position"), nb::arg("font_size"), nb::arg("tint"));
    m.def("draw_text_codepoints", &DrawTextCodepoints, "Draw multiple character (codepoint)", nb::arg("font"), nb::arg("codepoints"), nb::arg("codepoint_count"), nb::arg("position"), nb::arg("font_size"), nb::arg("spacing"), nb::arg("tint"));
}


void export_shader_management(nb::module_& m)
{

    m.def("load_shader",&LoadShader, "Load shader from files and bind default locations", nb::arg("vs_filename"), nb::arg("fs_filename"));
    m.def("load_shader_from_memory",&LoadShaderFromMemory, "Load shader from code strings and bind default locations", nb::arg("vs_code"), nb::arg("fs_code"));
    m.def("is_shader_valid",&IsShaderValid, "Check if a shader is valid (loaded on GPU)", nb::arg("shader"));
    m.def("get_shader_location",&GetShaderLocation, "Get shader uniform location", nb::arg("shader"), nb::arg("name"));
    m.def("get_shader_location_attrib",&GetShaderLocationAttrib, "Get shader attribute location", nb::arg("shader"), nb::arg("name"));
    m.def("set_shader_value", [](const Shader& shader, int locIndex,  nb::object value,int uniformType) {
        switch (uniformType) {
            case SHADER_UNIFORM_FLOAT:{
                const float floatValue = nb::cast<float>(value);
                SetShaderValue(shader, locIndex, &floatValue, uniformType);
                break;
            }
            case SHADER_UNIFORM_VEC2:
            {
                const Vector2 vec2Value = nb::cast<Vector2>(value);
                SetShaderValue(shader, locIndex, &vec2Value, uniformType);
                break;
            }
            case SHADER_UNIFORM_VEC3:
            {   
                const Vector3 vec3Value = nb::cast<Vector3>(value);
                SetShaderValue(shader, locIndex, &vec3Value, uniformType);
                break;
            }
            case SHADER_UNIFORM_VEC4:
            {
                const Vector4 vec4Value = nb::cast<Vector4>(value);
                SetShaderValue(shader, locIndex, &vec4Value, uniformType);
                break;
            }
            case SHADER_UNIFORM_INT:
            {
                const int intValue = nb::cast<int>(value);
                SetShaderValue(shader, locIndex, &intValue, uniformType);
                break;
            }
            case SHADER_UNIFORM_IVEC2:
            {
                std::array<int, 2> ivec2 = { nb::cast<int>(value[0]), nb::cast<int>(value[1]) };
                SetShaderValue(shader, locIndex, &ivec2, uniformType);
                break;
            }
            case SHADER_UNIFORM_IVEC3:
            {
                std::array<int, 3> ivec3 = { nb::cast<int>(value[0]), nb::cast<int>(value[1]), nb::cast<int>(value[2]) };
                SetShaderValue(shader, locIndex, &ivec3, uniformType);
                break;
            }
            case SHADER_UNIFORM_IVEC4:
            {
                std::array<int, 4> ivec4 = { nb::cast<int>(value[0]), nb::cast<int>(value[1]), nb::cast<int>(value[2]), nb::cast<int>(value[3]) };
                SetShaderValue(shader, locIndex, &ivec4, uniformType);
                break;
            }
            case SHADER_UNIFORM_SAMPLER2D:
            {
                throw std::runtime_error("Setting sampler2D uniforms is not yet implemented");
            }
            default:
                throw std::invalid_argument("Unsupported shader uniform type");
        }
    });
    m.def("set_shader_value_v", [](const Shader& shader,int locIndex, nb::object value, int uniformType) {
        switch (uniformType) {
            case SHADER_UNIFORM_FLOAT:{
                auto floatArray = nb::cast<nb::ndarray<float, nb::numpy, nb::shape<-1>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, floatArray.data(), uniformType, floatArray.shape(0));
            }
            case SHADER_UNIFORM_VEC2:
            {
                auto vec2Array = nb::cast<nb::ndarray<float, nb::numpy, nb::shape<-1, 2>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, vec2Array.data(), uniformType, vec2Array.shape(0));   
            }
            case SHADER_UNIFORM_VEC3:
            {
                auto vec3Array = nb::cast<nb::ndarray<float, nb::numpy, nb::shape<-1, 3>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, vec3Array.data(), uniformType, vec3Array.shape(0));
            }
            case SHADER_UNIFORM_VEC4:
            {
                auto vec4Array = nb::cast<nb::ndarray<float, nb::numpy, nb::shape<-1, 4>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, vec4Array.data(), uniformType, vec4Array.shape(0));
            }
            case SHADER_UNIFORM_INT:
            {
                auto intArray = nb::cast<nb::ndarray<int, nb::numpy, nb::shape<-1>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, intArray.data(), uniformType, intArray.shape(0));
            }
            case SHADER_UNIFORM_IVEC2:
            {
                auto ivec2Array = nb::cast<nb::ndarray<int, nb::numpy, nb::shape<-1, 2>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, ivec2Array.data(), uniformType, ivec2Array.shape(0));
            }
            case SHADER_UNIFORM_IVEC3:
            {
                auto ivec3Array = nb::cast<nb::ndarray<int, nb::numpy, nb::shape<-1, 3>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, ivec3Array.data(), uniformType, ivec3Array.shape(0));
            }
            case SHADER_UNIFORM_IVEC4:
            {
                auto ivec4Array = nb::cast<nb::ndarray<int, nb::numpy, nb::shape<-1, 4>, nb::c_contig>>(value);
                SetShaderValueV(shader, locIndex, ivec4Array.data(), uniformType, ivec4Array.shape(0));
            }
            case SHADER_UNIFORM_SAMPLER2D:
            {
                throw std::runtime_error("Setting sampler2D uniforms is not yet implemented");
            }
            default:{
                throw std::invalid_argument("Unsupported shader uniform type");
            }
        }
    });
    m.def("set_shader_value_matrix", &SetShaderValueMatrix, "Set shader value (matrix 4x4)", nb::arg("shader"), nb::arg("loc_index"), nb::arg("mat"));
    m.def("set_shader_value_texture", &SetShaderValueTexture, "Set shader value (texture)", nb::arg("shader"), nb::arg("loc_index"), nb::arg("texture"));
    m.def("unload_shader", &UnloadShader, "Unload shader from GPU", nb::arg("shader"));
}


void export_rcore(nb::module_& m)
{
    export_window(m);
    export_cursor(m);
    export_drawing(m);
    export_input_handling(m);
    export_timing(m);
    export_screen_space(m);
    export_shader_management(m);

}

