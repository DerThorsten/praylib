from .raylib import window_should_close
from time import perf_counter
# has pyjs
has_pyjs = False
try:
    import pyjs
    has_pyjs = True
except ImportError:
    has_pyjs = False



if has_pyjs:
    def set_main_loop_callback(func):
        pyjs.set_main_loop_callback(func, 0)

else:
    def set_main_loop_callback(func):
        # just loop
        last_t = perf_counter()
        while not window_should_close():
            curr_t = perf_counter()
            dt = curr_t - last_t
            last_t = curr_t
            func(dt)