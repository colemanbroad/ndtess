
import pytest
import numpy as np
from . import context
from . import tesselations as tess
from . import label_tools

from scipy.ndimage import label
from skimage.filters import gaussian

test_resources_dir = context.test_resources
import os.path as path



def test_tessellate_on_random_points(default_synthetic):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    vorimg = tess.tessellate_labimg(default_synthetic['lab'])
    vorimg2 = tess.tessellate_labimg(default_synthetic['lab'], default_synthetic['distimg'])
    mask = default_synthetic['lab']!=0

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert np.alltrue(vorimg[mask] == default_synthetic['lab'][mask])
    assert np.alltrue(vorimg2[mask] == default_synthetic['lab'][mask])
    ## The results are correct according to visual inspection :)
    # return vorimg, vorimg2
    # assert vorimg == default_synthetic['result']

def test_tessellate_on_null_image(default_synthetic):
    """
    run the tesselation on a empty image
    """
    allnull = np.zeros(default_synthetic['lab'].shape,dtype=np.int8)
    vorimg = tess.tessellate_labimg(allnull) #, load_state['distimg'])
    assert type(vorimg) != type(None)
    assert vorimg.shape == allnull.shape
    assert np.alltrue(vorimg == allnull)

def test_tessellate_on_geom_bodies(default_synthetic):
    """
    run the tesselation on an image with a circle, a bar and a rectangle
    """
    vorimg = tess.tessellate_labimg(default_synthetic['img'])
    assert np.any(vorimg != 0)

    #circle
    circlemask = (default_synthetic["result"][:,:,1]!=0)
    assert np.alltrue(vorimg[circlemask] != 0)
    assert np.alltrue(vorimg[:5,:5] == vorimg[0,0])
    assert np.alltrue(vorimg[:5,:5] == 30)
    assert np.alltrue(vorimg[16,16] == 30)

    #tilted bar
    barmask = (default_synthetic["result"][:,:,2]!=0)
    assert np.alltrue(vorimg[barmask] != 0)
    assert np.alltrue(vorimg[60:,60:] == 100) #not inside the object
    assert np.alltrue(vorimg[46:50,28] == 100) #inside the object

    rectmask = (default_synthetic["result"][:,:,0]!=0)
    assert np.alltrue(vorimg[rectmask] != 0)

def test_tessellate_on_geom_bodies_with_distimg(default_synthetic):
    """
    run the tesselation on an image with a circle, a bar and a rectangle using an arbitrary distimg to start
    """
    vorimg = tess.tessellate_labimg(default_synthetic['img'], default_synthetic['distimg'])
    assert np.any(vorimg != 0)

    #circle
    circlemask = (default_synthetic["result"][:,:,1]!=0)
    assert np.alltrue(vorimg[circlemask] != 0)
    assert np.alltrue(vorimg[:5,:5] == vorimg[0,0])
    assert np.alltrue(vorimg[:5,:5] == 30)
    assert np.alltrue(vorimg[16,16] == 30)

    #tilted bar
    barmask = (default_synthetic["result"][:,:,2]!=0)
    assert np.alltrue(vorimg[barmask] != 0)
    assert np.alltrue(vorimg[60:,60:] == 100) #not inside the object
    assert np.alltrue(vorimg[46:50,28] == 100) #inside the object

    rectmask = (default_synthetic["result"][:,:,0]!=0)
    assert np.alltrue(vorimg[rectmask] != 0)
