
import pytest
import numpy as np
import ndtess as tess
from . import printers
from . import tesselations as pytess

def test_on_map_of_0s(synthetic_checkerboard):
    """
    run the tesselation on a empty image
    """
    img = synthetic_checkerboard['img']
    di = np.zeros_like(img)

    cpp_vorimg = tess.tessellate_labimg(img,di)

    py_vorimg = pytess.tessellate_labimg(img,di)
    assert np.alltrue(py_vorimg[:4,:4] == 1)
    printers.store_ndarray("py_voronoi_on_map_of_0s_output.txt",py_vorimg)

    assert cpp_vorimg.size > 0
    assert cpp_vorimg.shape == synthetic_checkerboard['img'].shape
    assert np.alltrue(synthetic_checkerboard['img'][1:3,1:3] == 1)

    printers.store_ndarray("cpp_voronoi_input.txt",img)
    printers.store_ndarray("cpp_voronoi_on_map_of_0s_output.txt",cpp_vorimg)

    assert np.alltrue(cpp_vorimg[:4,:4] == 1)
