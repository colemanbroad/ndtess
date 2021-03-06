import pytest
import numpy as np

np.random.seed(1307) #the zip code of the MPI CBG


@pytest.fixture(scope="module")
def synthetic_checkerboard():
    """ creates a 16x16 ndarray and inserts small rectangle islands for each checkerboard style tile, each tile has size 4x4 """
    #populate squares, lines and circles at random positions
    img = np.zeros((16,16),dtype=np.float32)

    ## the "distance" between adjacent pixels (i0,i1) and (j0,j1) in labimg
    ## is given by `d = distimg[i0,i1] + distimg[j0,j1]`, thus distimg must be
    ## everywhere > 0

    margin = 1
    nblocks_per_dim = 4
    stride = int(np.round(img.shape[1]/nblocks_per_dim))
    blockid = 1

    for y in range(nblocks_per_dim):
        ylo = y*stride + margin
        yhi = (y+1)*stride - margin

        for x in range(nblocks_per_dim):
            xlo = x*stride + margin
            xhi = (x+1)*stride - margin

            img[ ylo:yhi , xlo:xhi  ] = (blockid)
            blockid += 1

    #distimg can be any distribution of non-zero floating point numbers
    distimg = np.random.rand(*img.shape)*3.3
    cdi = np.zeros_like(img).astype("float32")
    cdi[:] = 3.3 #some number

    sinargs = np.linspace(0,1,num=img.size).reshape(img.shape)
    sindistimg = np.sin( sinargs ) + .1

    assert np.alltrue(distimg >= 0.)

    return { 'img' : img, 'distimg' : distimg , 'cdi' : cdi , 'sindi' : sindistimg}

@pytest.fixture(scope="module")
def load_synthetic():
    """ creates a 16x16 ndarray and inserts a rectangle at (x,y)=(1:5,11:15) with value 42 and a circle at (x,y) = (12,4) with radius 4 with value 100
    """

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

@pytest.fixture(scope="module")
def default_synthetic():
    """ creates 64x64 ndarray of 0s and inserts 3 islands (a rectangle, a circle and a diagonal bar """

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
