import praylib as pray
import numpy as np
from pathlib import Path
import itertools

this_dir = Path(__file__).parent
shader_dir = this_dir / "shader"


win_size = (800, 800)
screen_width = win_size[0]
screen_height = win_size[1]
pray.init_window(*win_size, "Praylib Window")

img_blank = pray.gen_image_color(1024, 1024, pray.BLANK)
texture = pray.load_texture_from_image(img_blank)
pray.unload_image(img_blank)

# load texture "emscripten_forge.png"
logo = pray.load_image(str(this_dir/"emscripten_forge.png"))
logo_texture = pray.load_texture_from_image(logo)
pray.unload_image(logo)

if pray.is_web():
    GLSL_VERSION = 100
else:
    GLSL_VERSION = 330

shader_path = str(shader_dir / f"glsl{GLSL_VERSION}/cubes_panning.fs")
shader = pray.load_shader("",shader_path)

class Shader:
    def __init__(self):
        self.time = 0.0
        self.time_loc = pray.get_shader_location(shader, "uTime")
        pray.set_shader_value(shader, self.time_loc, self.time, pray.SHADER_UNIFORM_FLOAT)

        self.all_line_strokes = []
        self.line_stroke = []
        self.max_age = 0.5
        self.base_radius = 15.0
        self.zoom = 1.0

    def age_to_radius(self, age):
        # linear interpolation between base_radius and 0
        rel_age = age / self.max_age
        return self.base_radius * (1.0 - rel_age)

    def age_to_color(self, age):
        rel_age = age / self.max_age
        return pray.Color(
            int(255 * (1.0 - rel_age)),
            int(255 * rel_age),
            0,
            255
        )

        
    def __call__(self, dt):
        self.time += dt
        pray.set_shader_value(shader, self.time_loc, self.time, pray.SHADER_UNIFORM_FLOAT)

        with pray.drawing_ctx():
            pray.clear_background(pray.RAYWHITE)


            with pray.shader_ctx(shader):
                pray.draw_texture(texture, 0, 0, pray.WHITE)

            # roate the image via camera2d
            cam = pray.Camera2D()
            cam.target = (screen_width/2, screen_height/2)
            cam.offset = (screen_width/2, screen_height/2)
            cam.rotation = self.time * 10
            cam.zoom = 1.0
            with pray.mode_2d_ctx(cam):
                pray.draw_texture(logo_texture, int(screen_width/2 - logo_texture.width/2), int(screen_height/2 - logo_texture.height/2), pray.WHITE)



            pos = pray.get_mouse_position()

            if pray.is_mouse_button_down(0):
                delta = pray.get_mouse_delta().length()
                if delta > 0.0:
                    now = pray.get_time()
                    self.line_stroke.append((pos, now))
                
            if pray.is_mouse_button_released(0):
                self.all_line_strokes.append(self.line_stroke)
                self.line_stroke = []
            



            new_all_strokes = []

            for strokes in itertools.chain(self.all_line_strokes, [self.line_stroke]):
                new_strokes = []
                last_point = None
                for point, time in strokes:
                    age = pray.get_time() - time
                    if age < self.max_age:
                        radius = self.age_to_radius(age)
                        color = self.age_to_color(age)
                        pray.draw_circle_v(point, radius, color)    
                        new_strokes.append((point, time))
                        if last_point is not None:
                            pray.draw_line_ex(last_point, point, radius * 2, color)
                        last_point = point
                if new_strokes:
                    new_all_strokes.append(new_strokes)
            

            # Draw the FPS counter
            pray.draw_fps(10, 10)


pray.set_main_loop_callback(Shader())