from .raylib import (
    begin_drawing,
    end_drawing,
    begin_mode_2d,
    end_mode_2d,
    begin_shader_mode,
    end_shader_mode,
    Camera2D
)

from contextlib import contextmanager

@contextmanager
def drawing_ctx():
    """Context manager for drawing operations.
        this wraps begin_drawing()/end_drawing() in a context
    """
    begin_drawing()
    try:
        yield
    finally:
        end_drawing()


@contextmanager
def mode_2d_ctx(camera: Camera2D):
    """Context manager for 2D camera operations.
        this wraps begin_mode_2d()/end_mode_2d() in a context
    """
    begin_mode_2d(camera)
    try:
        yield
    finally:
        end_mode_2d()

@contextmanager
def shader_ctx(shader):
    """Context manager for shader operations.
        this wraps begin_shader_mode()/end_shader_mode() in a context
    """
    begin_shader_mode(shader)
    try:
        yield
    finally:
        end_shader_mode()
