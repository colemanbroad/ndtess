import heapq

import pytest
import numpy as np

from . import tesselations as tess
from . import printers



def test_heapq_init_from_zeroes(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """
    di = np.zeros_like(load_synthetic["img"]).astype("float32")
    q = tess.initialize_heapq(load_synthetic["img"],di)

    assert q[0]
    assert q[0][-1] == 100.

    # printers.store_ndarray("test_heapq_init_from_zeroes_input.ndarray",load_synthetic["img"] )
    # printers.store_heaplist("test_heapq_init_from_zeroes.hq",q )


def test_heapq_init_from_constant(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    assert load_synthetic["cdi"].shape == load_synthetic["img"].shape
    assert np.allclose(load_synthetic["cdi"], 3.3)

    q = tess.initialize_heapq(load_synthetic["img"],
                              load_synthetic["cdi"])


    assert q[0]
    assert q[0][-1] == 100.
    # printers.store_ndarray("test_heapq_init_from_constant_input.ndarray",load_synthetic["img"] )
    # printers.store_heaplist("test_heapq_init_from_constant.hq",q )


def test_heapq_init_from_sinus(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    assert load_synthetic["cdi"].shape == load_synthetic["img"].shape

    q = tess.initialize_heapq(load_synthetic["img"],
                              load_synthetic["sindi"])


    assert q[0]
    assert q[0][-1] == 100.
    assert q[0][1] == 0
    assert q[0][2] == 10
    # printers.store_ndarray("test_heapq_init_from_sinus_input.ndarray",load_synthetic["img"] )
    # printers.store_heaplist("test_heapq_init_from_sinus.hq",q )

# def test_heapq_init_from_random(load_synthetic):
#     """
#     run the tesselation on a labelled image where all objects have been identified already (null test)
#     """

#     assert load_synthetic["cdi"].shape == load_synthetic["img"].shape

#     q = tess.initialize_heapq(load_synthetic["img"],
#                               load_synthetic["di"])


#     assert q[0]
#     assert q[0][-1] == 100.
#     assert q[0][1] == 5
#     assert q[0][2] == 13

#     # printers.store_ndarray("test_heapq_init_from_random_input.ndarray",load_synthetic["img"] )
#     # printers.store_heaplist("test_heapq_init_from_random.hq",q )
