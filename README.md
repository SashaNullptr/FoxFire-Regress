# FoxFire/regression![foxfire-logo](logo_sized.png)

`regression` is a component of the `FoxFire`
project that handles regularized linear regression.

This module provides implementations of L<sub>1</sub> and
L<sub>0</sub> regularized regression, with optional GPGPU acceleration via OpenCL.

## Supported Platforms

This module currently supports Windows, OS X and Linux.

## Installation

This module is header-only meaning
 there is no installation step -- just clone the git repository and `#include`
 the appropriate source files in your C++ projects. Just be sure to include / link against the
appropriate dependencies, as outlined in the *Dependencies* section below.

This module contains both generic and OpenCL specific components.

### Plain Installation ( No OpenCL )

The base module requires the [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page)
linear algebra library. Eigen3 is header-only, so the only additional step
required is the include the Eigen3 root directory `eigen3` during compilation. For example,
on Linux systems one would pass the `-I/usr/include/eigen3` to the appropiate compilier.

A sample GCC configuration might look like `g++ $PROGRAM -I/usr/include/eigen3`

### GPGPU Accelerated Installation ( Requires OpenCL )

In order to use GPGPU acceleration a valid OpenCL installation and at least one
OpenCL compatible compute device are required. In addition the [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page)
and [ViennaCL](http://viennacl.sourceforge.net/) libraries need to installed. Some
special macros need to passed during program compilation, these are `VIENNACL_WITH_OPENCL`
and `VIENNACL_WITH_OPENCL`.

A sample GCC command might look like `g++ $PROGRAM -DVIENNACL_WITH_OPENCL -DVIENNACL_WITH_EIGEN -I/usr/include/eigen3 -I/usr/include/viennacl -I/usr/local/cuda/include -L/usr/local/cuda/lib64 -lOpenCL`

## Licensing

The `FoxFire-regression` package is licensed under the MIT license. To
view the MIT license please consult `LICENSE.txt`.

## Acknowledgements

`FoxFire-regression` is based on the [FOS](https://github.com/LedererLab/FOS)
package produced by Johannes Lederer, Néhémy Lim and Saba Noorassa as part of the
 `HDIM` research group.
