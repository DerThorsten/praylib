from .raylib import (
    begin_drawing,
    end_drawing,
    begin_mode_2d,
    end_mode_2d,
    Camera2D
)


from contextlib import contextmanager


@contextmanager
def drawing_ctx():
    """Context manager for drawing operations."""
    begin_drawing()
    try:
        yield
    finally:
        end_drawing()


@contextmanager
def mode_2d_ctx(camera: Camera2D):
    """Context manager for 2D camera operations."""
    begin_mode_2d(camera)
    try:
        yield
    finally:
        end_mode_2d()