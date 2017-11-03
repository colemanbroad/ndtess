import ndtess
import numpy

def test_add_scalars():
    """ test access to our api """
    result = 0
    rhs = 1

    result = ndtess.add_scalars(rhs,rhs)

    assert result != rhs
    assert result == 2


def test_add_numpy_vectors():
    """ test access to our api """
    result = numpy.zeros((32,32))
    rhs = numpy.ones((32,32))

    result = ndtess.add_vectors(rhs,rhs)

    assert result != rhs
