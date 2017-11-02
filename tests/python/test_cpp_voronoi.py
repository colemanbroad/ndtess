
import pytest
import numpy as np
import ndtess as tess

from scipy.ndimage import label
from skimage.filters import gaussian

test_resources_dir = context.test_resources
import os.path as path


@pytest.fixture(scope="module")
def load_synthetic():

    #populate squares, lines and circles at random positions
    img = np.zeros((64,64),dtype=np.float32)

    classimg = np.zeros((64,64,3),dtype=np.int8)

    #a rectangle of intensity 42
    img[30:50,30:40] = 42
    classimg[30:50,30:40,0] = 1 #circles are class 1

    #a circle at (15,15) with radius = 10 of intensity 30
    radius = 10
    for y in range(5,25):
        y_extend = 15 - y
        x_extend = int(np.sqrt((radius*radius) - (y_extend*y_extend)))
        img[(15-x_extend):(15+x_extend), y] = 30
        classimg[(15-x_extend):(15+x_extend), y, 1] = 2 #circles are class 2

    #a tilted bar from (35,0) - [59,54]
    for x in range(35,60):
        ylo = 2*x - 70
        yhi = 2*x - 64
        img[x,ylo:yhi] = 100
        classimg[x,ylo:yhi,2] = 3 #tilted bar is class 3

    # #something for later
    # noise = np.random.normal(5,3,64*64).reshape(img.shape)
    # noisy_img = np.zeros((64,64),dtype=np.float32)
    # noisy_img = noisy_img + noise + img

    ## label image is build with labelled seeds
    ## we could also do this by using `scipy.ndimage.label()` on a binary mask...
    labimg = np.zeros(img.shape,dtype=np.int8)
    seeds0 = np.random.randint(0, labimg.shape[0], 11)
    seeds1 = np.random.randint(0, labimg.shape[1], 11)

    labimg[seeds0, seeds1] = np.arange(1, len(seeds1)+1, dtype=np.int8)

    ## the "distance" between adjacent pixels (i0,i1) and (j0,j1) in labimg
    ## is given by `d = distimg[i0,i1] + distimg[j0,j1]`, thus distimg must be
    ## everywhere > 0

    #distimg can be any distribution of non-zero floating point numbers
    distimg = np.random.rand(*labimg.shape)*3.3

    assert np.alltrue(distimg >= 0.)

    return { 'img' : img, 'distimg' : distimg, 'lab' : labimg, 'result' : classimg ,  }


def test_tessellate_on_null_image(load_synthetic):
    """
    run the tesselation on a empty image
    """
    allnull = load_synthetic['lab'].copy()
    allnull[...] = 0
    vorimg = tess.tessellate_labimg(allnull) #, load_state['distimg'])
    assert type(vorimg) != type(None)
    assert vorimg.shape != allnull.shape
    assert vorimg == allnull
