import praylib as pray
import numpy as np
import itertools

win_size = (800, 600)
pray.init_window(*win_size, "Praylib Window")






class MouseTrace:
    def __init__(self):
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



        # zoom on mousewheel
        if pray.get_mouse_wheel_move() != 0:
            self.zoom += pray.get_mouse_wheel_move() * 0.1
            self.zoom = max(0.1, min(self.zoom, 10.0))

        with pray.drawing_ctx():  

            camera = pray.Camera2D()
            camera.zoom = self.zoom

            with pray.mode_2d_ctx(camera):
             

                pray.clear_background(pray.Color(0, 0, 0, 255))
                screen_pos = pray.get_mouse_position()
                pos = pray.get_screen_to_world_2d(screen_pos, camera)


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



if __name__ == "__main__":
    example = MouseTrace()
    pray.set_main_loop_callback(example)