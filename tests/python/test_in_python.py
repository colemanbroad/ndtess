import pytest
import ndtess
import numpy

def test_access_api():
    """ test access to our api """
    result = numpy.zeros((32,32))
    rhs = numpy.ones((32,32))

    result = ndtess.add(rhs,rhs)

    assert result != rhs
