import os
import re
import sys
import sysconfig
import platform
import subprocess

from distutils.version import LooseVersion
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):

    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):

    user_options = [('cmake-args=', 'C', "Arguments to pass to cmake call"),
                    ('build-args=', 'A', "Arguments to pass to cmake build command (after --)")
    ]

    def initialize_options(self):
        self.user_cmake_args = None
        self.user_build_args = None

    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)',
                                         out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(
                cfg.upper(),
                extdir)]
            if sys.maxsize > 2**32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j4']

        if self.user_cmake_args:
            cmake_args += self.user_cmake_args

        if self.user_build_args:
            build_args += self.user_build_args

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        print("[setup.py] calling cmake in ",self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args,
                              cwd=self.build_temp, env=env)

        subprocess.check_call(['cmake', '--build', '.'] + build_args,
                              cwd=self.build_temp)
        print()  # Add an empty line for cleaner output


from setuptools.command.test import test as st_test

class CatchTestCommand(st_test):
    """
    A custom test runner to execute both Python unittest tests and C++ Catch-
    lib tests.
    """
    user_options = [('pytest-args=', 'P', "Arguments to pass to pytest"),('ctest-args=', 'C', "Arguments to pass to ctest")]

    def initialize_options(self):
        self.pytest_args = None
        self.ctest_args = None

    def distutils_dir_name(self, dname):
        """Returns the name of a distutils build directory"""
        dir_name = "{dirname}.{platform}-{version[0]}.{version[1]}"
        value = dir_name.format(dirname=dname,
                               platform=sysconfig.get_platform(),
                               version=sys.version_info)
        print("[CatchTestCommand.distutils_dir_name] ",value)
        return value


    def run_tests(self):
        import shlex
        import pytest

        # Run ctest
        cmd = ['ctest']
        if self.ctest_args:
            cmd += shlex.split(self.ctest_args)

        errno = subprocess.call(cmd,
                                cwd=os.path.join('build',
                                                 self.distutils_dir_name('temp')),
                                shell=True)

        # Run pytest and add the error code
        pyt_cmd = []
        if self.pytest_args:
            pyt_cmd = shlex.split(self.pytest_args)
        pyt_cmd += ["tests/python"]
        errno = errno + pytest.main(pyt_cmd)
        sys.exit(errno)


    def initialize_options(self):
        st_test.initialize_options(self)
        self.pytest_args = ''
        self.ctest_args = ''


setup(
    name='ndtess',
    version='0.1',
    author='Coleman Broaddus, Peter Steinbach',
    author_email='broaddus@mpi-cbg.de',
    description='tessellates your ndarrays using a generalized voronoi algorithm for graphs',
    long_description='',
    # add extension module
    ext_modules=[CMakeExtension('ndtess')],
    # add custom build_ext command
    tests_requires=['pytest'],
    cmdclass={'build_ext' : CMakeBuild, 'test':CatchTestCommand},
    zip_safe=False,
)
