
import pytest
import numpy as np

from . import tesselations as tess

np.random.seed(1307) #the zip code of the MPI CBG

@pytest.fixture(scope="module")
def load_synthetic():

    #populate squares, lines and circles at random positions
    img = np.zeros((16,16),dtype=np.float16)

    #a rectangle of intensity 42
    img[11:15, 1:5] = 42

    #a circle at (15,15) with radius = 10 of intensity 30
    radius = 4
    for y in range(0,16):
        for x in range(0,16):
            y_extend = y - 4
            x_extend = x - 12
            if ((x_extend**2)+(y_extend**2)) < radius**2:
                img[y,x] = 100


    #distimg can be any distribution of non-zero floating point numbers
    distimg = np.random.rand(*img.shape)*3.3
    cdi = np.zeros_like(img).astype("float32")
    cdi[:] = 3.3 #some number


    sinargs = np.linspace(0,1,num=img.size).reshape(img.shape)
    sindistimg = np.sin( sinargs ) + .1

    return { 'img' : img, 'di' : distimg, 'cdi' : cdi, 'sindi' : sindistimg }


def test_heapq_init_from_zeroes(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """
    di = np.zeros_like(load_synthetic["img"]).astype("float32")
    q = tess.initialize_heapq(load_synthetic["img"],di)

    vorimg = build_vorimg(q,
                          load_synthetic["img"],
                          di)

    assert vorimg[0,0]
