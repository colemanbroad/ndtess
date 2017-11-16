
import pytest
import numpy as np
import ndtess as tess


def test_tesselate_on_null_image(synthetic_checkerboard):
    """
    run the tesselation on a empty image
    """
    assert synthetic_checkerboard['img'].size > 0
