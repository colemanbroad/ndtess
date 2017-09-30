# ndtess 

tessellates your ndarrays using a generalized voronoi algorithm for graphs

## How to build

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

## Python Tests

Testing relies on binary resources (images) located in `ndtess/test_resources/`.

```
$ cd ndtess
$ py.test tests/
# more thorough testing
$ py.test tests/ --runslow
```