# ndtess 

tessellates your ndarrays using a generalized voronoi algorithm for graphs

## How to build

## Dependencies

- to build the package
    + python 3 (tested with 3.5.4)
    + C++ compiler with C++14 support (tested with gcc 6.4.1 and clang 3.9.1)
    + cmake (tested with 3.9.1)
    + numpy (tested with 1.11.2)
    
- to run the tests
    + pytest-3 (tested with 2.9.2)
    + pytest-benchmark (tested with 3.1.1)
    + scipy (tested with 0.18.1)
    + scikit-image (tested with 0.12.3)

## Pythonic

```
$ git clone git@github.com:colemanbroad/ndtess.git
$ cd ndtess
$ python3 ./setup install --user
$ python3 ./setup test 
```

The test suite requires [pytest-3](https://docs.pytest.org/en/latest/contents.html) and [pytest-benchmark](https://pypi.python.org/pypi/pytest-benchmark).

## CMake based

This project is supported on Linux and macOS only. We tested with gcc 6.3.1 on Fedora 25 and Xcode8 on macOS.

```
$ git clone https://github.com/colemanbroad/ndtess.git
$ cd ndtess
$ mkdir build
$ cd build
$ cmake ..
$ cmake tests .. #optional
```

### cmake flags

- `-DWITH_TESTS` enable unit tests (possible values `ON`/`OFF`, default: `ON`)

