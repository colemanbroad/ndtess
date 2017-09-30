import pytest
import numpy as np
from . import context
from . import tesselations as tess
from . import label_tools

test_resources_dir = context.test_resources
import os.path as path

@pytest.fixture(scope="module")
def load_state():
    import skimage.io as io
    from scipy.ndimage import label
    from skimage.filters import gaussian
    img = io.imread(path.join(test_resources_dir, 'microtubule foams.jpg'))
    pimg = np.load(path.join(test_resources_dir, 'microtubule foams_Probabilities Stage 2.npy'))
    vorimg = io.imread(path.join(test_resources_dir, 'vorimg.tif'))
    pimg = pimg.astype('float16')
    distimg = pimg[:,:,1].copy().astype('float32')
    distimg = gaussian(distimg, 30)
    bimg = pimg[...,0] > 0.9
    lab, nc = label(bimg)
    coords, labels = label_tools.get_coords_and_labels(lab)
    ## WARNING: THIS DOESN'T WORK! LABELS MAY HAVE HOLES.
    # coords_int = coords.copy().astype('int')
    # labels  = lab[coords_int[:,0], coords_int[:,1]]    

    state = {'img'     : img,
             'pimg'    : pimg,
             'lab'     : lab,
             'labels'  : labels,
             'distimg' : distimg,
             'coords'  : coords,
             'vorimg'  : vorimg,
             # 'coords_i': coords_int,
             }
    return state

def test_loaddata(load_state):
    img    = load_state['img']
    pimg   = load_state['pimg']
    lab    = load_state['lab']
    coords = load_state['coords']
    labels = load_state['labels']

    assert img.shape == (1024, 1344)
    assert pimg.shape == (1024, 1344, 3)
    assert img.sum() == 99327422
    assert coords.shape == (51,2)
    assert np.alltrue(np.unique(lab) == np.arange(52))
    assert np.alltrue(labels == np.arange(51)+1)
    assert coords.std() > 368

def test_buildHeapqCoords(load_state):
    coords = load_state['coords']
    labels = load_state['labels']
    distimg = load_state['distimg']
    heap, vorimg = tess.initialize_heapq_coords(coords, labels, distimg)

def test_scipyVoronoi(load_state):
    coords = load_state['coords']
    img    = load_state['img']
    fig, vor = tess.show_basic_voronoi_img(coords, img)

def test_labimg_boundaries(load_state):
    lab = load_state['lab']
    vorimg = load_state['vorimg']
    bimg = label_tools.detect_labimg_boundaries(vorimg)
    # res = np.stack([lab, bimg]).astype('int')
    # print(bimg)
    # print(np.unique(bimg))
    # return bimg
    assert bimg.dtype == np.uint8
    assert set(np.unique(bimg)) < {0,1,2,3,4}
    assert set(np.unique(bimg)) == {1,2,3,4}

@pytest.mark.slow
def test_heapq_and_vorimg(load_state):
    lab    = load_state['lab']
    distimg = load_state['distimg']
    heap = tess.initialize_heapq(lab, distimg)
    assert len(heap) > 30000
    vorimg = tess.build_vorimg(heap, lab, distimg)
    mask = vorimg==0
    assert mask.sum()==0
    assert np.alltrue(np.unique(vorimg) == np.unique(lab)[1:])
    return vorimg

@pytest.mark.slow
def test_tessellate_flat(load_state):
    """
    distance image is taken to be const
    """
    vorimg = tess.tessellate_labimg(load_state['lab']) #, load_state['distimg'])
    return vorimg


