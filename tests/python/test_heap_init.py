
import pytest
import numpy as np

from . import tesselations as tess

np.random.seed(1307) #the zip code of the MPI CBG

@pytest.fixture(scope="module")
def load_synthetic():

    #populate squares, lines and circles at random positions
    img = np.zeros((32,32),dtype=np.float32)

    #a rectangle of intensity 42
    img[6:11,2:5] = 42

    #a circle at (15,15) with radius = 10 of intensity 30
    # radius = 4
    # for y in range(0,32):
    #     for x in range(0,32):
    #         y_extend = y - 24
    #         x_extend = x - 24
    #         if ((x_extend**2)+(x_extend**2)) < radius**2:
    #             img[x,y] = 100


    #distimg can be any distribution of non-zero floating point numbers
    distimg = np.random.rand(*img.shape)*3.3

    return { 'img' : img, 'distimg' : distimg }


def test_heapq_init_from_zeroes(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """
    di = np.zeros_like(load_synthetic["img"]).astype("float32")
    q = tess.initialize_heapq(load_synthetic["img"],di)

    assert q[0]

    print(q[0], len(q))
