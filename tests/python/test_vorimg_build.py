
import pytest
import numpy as np

from . import tesselations as tess


def test_vorimg_from_zeroes(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """
    di = np.zeros_like(load_synthetic["img"]).astype("float32")
    q = tess.initialize_heapq(load_synthetic["img"],di)

    vorimg = tess.build_vorimg(q,
                               load_synthetic["img"],
                               di)

    assert vorimg[0,0]
    print("##",vorimg[0,0], load_synthetic["img"][0,0])
