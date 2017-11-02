
import pytest
import numpy as np
from . import context
from . import tesselations as tess
from . import label_tools

from scipy.ndimage import label
from skimage.filters import gaussian

test_resources_dir = context.test_resources
import os.path as path

np.random.seed(1307) #the zip code of the MPI CBG

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

    #Q: why do we set the value of the labelled image greater than the number of classes we have?
    labimg[seeds0, seeds1] = np.arange(1, len(seeds1)+1, dtype=np.int8)

    ## the "distance" between adjacent pixels (i0,i1) and (j0,j1) in labimg
    ## is given by `d = distimg[i0,i1] + distimg[j0,j1]`, thus distimg must be
    ## everywhere > 0

    #distimg can be any distribution of non-zero floating point numbers
    distimg = np.random.rand(*labimg.shape)*3.3

    assert np.alltrue(distimg >= 0.)

    return { 'img' : img, 'distimg' : distimg, 'lab' : labimg, 'result' : classimg ,  }


def test_tessellate_on_random_points(load_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """
    #Q: why not use img as the input? I thought lab was only needed to seed the algorithm?
    vorimg = tess.tessellate_labimg(load_synthetic['lab'])
    vorimg2 = tess.tessellate_labimg(load_synthetic['lab'], load_synthetic['distimg'])
    mask = load_synthetic['lab']!=0

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert np.alltrue(vorimg[mask] == load_synthetic['lab'][mask])
    assert np.alltrue(vorimg2[mask] == load_synthetic['lab'][mask])
    ## The results are correct according to visual inspection :)
    # return vorimg, vorimg2
    # assert vorimg == load_synthetic['result']

def test_tessellate_on_null_image(load_synthetic):
    """
    run the tesselation on a empty image
    """
    allnull = np.zeros(load_synthetic['lab'].shape,dtype=np.int8)
    vorimg = tess.tessellate_labimg(allnull) #, load_state['distimg'])
    assert type(vorimg) != type(None)
    assert vorimg.shape == allnull.shape
    assert np.alltrue(vorimg == allnull)

def test_tessellate_on_geom_bodies(load_synthetic):
    """
    run the tesselation on an image with a circle, a bar and a rectangle
    """
    vorimg = tess.tessellate_labimg(load_synthetic['img'])
    assert np.any(vorimg != 0)

    #circle
    circlemask = (load_synthetic["result"][:,:,1]!=0)
    assert np.alltrue(vorimg[circlemask] != 0)
    assert np.alltrue(vorimg[:5,:5] == vorimg[0,0])
    assert np.alltrue(vorimg[:5,:5] == 30)
    assert np.alltrue(vorimg[16,16] == 30)

    #tilted bar
    barmask = (load_synthetic["result"][:,:,2]!=0)
    assert np.alltrue(vorimg[barmask] != 0)
    assert np.alltrue(vorimg[60:,60:] == 100) #not inside the object
    assert np.alltrue(vorimg[46:50,28] == 100) #inside the object

    rectmask = (load_synthetic["result"][:,:,0]!=0)
    assert np.alltrue(vorimg[rectmask] != 0)

def test_tessellate_on_geom_bodies_with_distimg(load_synthetic):
    """
    run the tesselation on an image with a circle, a bar and a rectangle using an arbitrary distimg to start
    """
    vorimg = tess.tessellate_labimg(load_synthetic['img'], load_synthetic['distimg'])
    assert np.any(vorimg != 0)

    #circle
    circlemask = (load_synthetic["result"][:,:,1]!=0)
    assert np.alltrue(vorimg[circlemask] != 0)
    assert np.alltrue(vorimg[:5,:5] == vorimg[0,0])
    assert np.alltrue(vorimg[:5,:5] == 30)
    assert np.alltrue(vorimg[16,16] == 30)

    #tilted bar
    barmask = (load_synthetic["result"][:,:,2]!=0)
    assert np.alltrue(vorimg[barmask] != 0)
    assert np.alltrue(vorimg[60:,60:] == 100) #not inside the object
    assert np.alltrue(vorimg[46:50,28] == 100) #inside the object

    rectmask = (load_synthetic["result"][:,:,0]!=0)
    assert np.alltrue(vorimg[rectmask] != 0)
