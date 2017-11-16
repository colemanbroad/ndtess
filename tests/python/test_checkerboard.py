import os
import pytest
import numpy as np
from . import context
from . import tesselations as tess
from . import label_tools

#from . import printers

def test_tessellate_checkerboard_from_distmap_of_0(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    vorimg = tess.tessellate_labimg(img)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert vorimg[0,0] == 1
    assert vorimg[-1,-1] == 16

    # printers.store_ndarray("checkerboard_input.txt",img)
    # printers.store_ndarray("checkerboard_output_distmap0.txt",vorimg)


def test_tessellate_checkerboard_from_distmap_of_noise(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = synthetic_checkerboard['distimg']
    vorimg = tess.tessellate_labimg(img, di)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert vorimg[0,0] == 1
    assert vorimg[-1,-1] == 16

    # if not os.path.exists("checkerboard_input.txt"):
        # printers.store_ndarray("checkerboard_input.txt",img)
    # printers.store_ndarray("checkerboard_output_distmapnoise.txt",vorimg)


def test_tessellate_checkerboard_from_distmap_of_0_nonrowmajor(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    vorimg = tess.tessellate_labimg(img, row_major = False)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert vorimg[0,0] == 1
    assert vorimg[-1,-1] == 16

    # if not os.path.exists("checkerboard_input.txt"):
        # printers.store_ndarray("checkerboard_input.txt",img)
    # printers.store_ndarray("checkerboard_output_distmap0_nonrowmajor.txt",vorimg)


def test_tessellate_checkerboard_from_distmap_of_noise_nonrowmajor(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = synthetic_checkerboard['distimg']
    vorimg = tess.tessellate_labimg(img, di, row_major = False)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert vorimg[0,0] == 1
    assert vorimg[-1,-1] == 16

    # if not os.path.exists("checkerboard_input.txt"):
        # printers.store_ndarray("checkerboard_input.txt",img)
    # printers.store_ndarray("checkerboard_output_distmapnoise_nonrowmajor.txt",vorimg)


def test_checkerboard_heapq_from_distmap_of_0(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = np.zeros_like(img).astype("float32")
    hq = tess.initialize_heapq(img,di)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert hq[0]
    # if not os.path.exists("checkerboard_heapq_from_distmap_of_0.hq"):
        # printers.store_heaplist("checkerboard_heapq_from_distmap_of_0.hq",hq)

def test_checkerboard_heapq_from_distmap_of_0_nonrowmajor(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = np.zeros_like(img).astype("float32")
    hq = tess.initialize_heapq(img,di,row_major=False)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert hq[0]
    # if not os.path.exists("checkerboard_heapq_from_distmap_of_0_nonrowmajor.hq"):
        # printers.store_heaplist("checkerboard_heapq_from_distmap_of_0_nonrowmajor.hq",hq)


def test_checkerboard_heapq_from_distmap_of_noise(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = synthetic_checkerboard['distimg']
    hq = tess.initialize_heapq(img,di)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert hq[0]
#    # if not os.path.exists("checkerboard_heapq_from_distmap_of_noise.hq"):
        # printers.store_heaplist("checkerboard_heapq_from_distmap_of_noise.hq",hq)



def test_checkerboard_heapq_from_distmap_of_noise_nonrowmajor(synthetic_checkerboard):
    """
    run the tesselation on a labelled image where all objects have been identified already (null test)
    """

    img = synthetic_checkerboard['img']
    di = synthetic_checkerboard['distimg']
    hq = tess.initialize_heapq(img,di,row_major = False)

    ## Obviously, this is not a complete test for correctness, but it will catch the simplest bugs.
    assert hq[0]
    ## if not os.path.exists("checkerboard_heapq_from_distmap_of_noise_nonrowmajor.hq"):
        # printers.store_heaplist("checkerboard_heapq_from_distmap_of_noise_nonrowmajor.hq",hq)
