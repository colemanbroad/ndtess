import pytest
import ndtess as cpp_tess
from . import tesselations as py_tess
import numpy as np

def generate_data(_shape):

    img = np.zeros(_shape,dtype=np.float32)
    seeds0 = np.random.randint(0, img.shape[0], 32)
    seeds1 = np.random.randint(0, img.shape[1], 32)
    img[seeds0, seeds1] = np.arange(1, len(seeds1)+1, dtype=np.int8)

    di = np.zeros_like(img).astype("float32")

    return img,di

def test_python_256x256(benchmark):

    img,di = generate_data((256,256))

    result = benchmark(py_tess.tessellate_labimg, img,di)

    result

def test_cpp_256x256(benchmark):

    img,di = generate_data((256,256))

    result = benchmark(cpp_tess.tessellate_labimg, img,di)

    result
