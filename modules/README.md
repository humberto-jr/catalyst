# modules

## About

A collection of lightweight modules that wraps the boilerplate code required for calling the C/C++ standard library and third-party code. These would encapsulate type conversions, enforce const correctness, internal state management, error handling, thread safety, message passing, I/O, GPU use and synchronization, algorithms, math, etc. While it is intended to provide a clean, more readable and safe API, it should not become a barrier to accessing a lower-level API for the sake of, say, performance.

## Content

**libc.h**: The most fundamental module, which is included by everything else and provides all header files from the C standard library. It also includes the POSIX `unistd.h` header.

**types.h**: Provides immutable and mutable primitive type aliases using a modern naming convention and some helper functions. The immutable unsigned integers are `byte`, `u8`, `u16`, `u32`, `u64`, and `usize`; the immutable signed integers are `s8`, `s16`, `s32`, and `s64`; the immutable floating points are `f32`, `f64`, and `f128`; and the immutable complex floating points are `c32`, `c64`, and `c128`. The C literal string is renamed as `c_str`. The mutable type `T` is defined as `mut<T>`.

**print.h**: Provides the `print` namespace and the basic thread-safe functions `print::line()` and `print::error()` to write the `stdout` and `stderr` without the somewhat cumbersome use of C++ `std::cout` or the error-prone formattings of C `printf()`.

**vector.h**: Defines `Vec<T>`, an overly simple and lightweight dynamically allocated vector of type `T`.

**string.h**: Defines the primitive type `String` for dynamically allocated strings, in addition to various text formatting and management member functions.

**matrix.h**: Defines `Mat<T>`, a lightweight matrix abstraction built on top of `Vec<T>`. This module does not include linear algebra operations just yet.

**essentials.h**: For convenience, it includes the previous header files and the `omp.h` from the [OpenMP](https://www.openmp.org/) library (OMP) for threading usage. It also defines the global `MAX_HOST_THREAD_COUNT` constant and the `thread_count()` and `thread_id()` runtime functions.

**libgsl.h**: Includes all relevant [GSL](https://www.gnu.org/software/gsl/) header files used throughout the codebase. More headers are added on demand.

**libmpi.h**: Provides the `mpi` namespace, some helper functions, and the `mpi::Frontend` type, which wraps MPI-related internal states and functionalities of a given [Message Passing Interface](https://www.mpi-forum.org/) backend library. It uses C++ function overloading and type inference to alleviate the use of the original MPI API. If an MPI backend is not used, the API provided by this module becomes a collection of dummy no-op calls. Thus, higher-level codes won't need to be changed.

**nist.h**: Provides the `nist` namespace, and serves as a database for all relevant NIST [fundamental physical constants](https://pml.nist.gov/cuu/Constants/Table/allascii.txt), NIST [atomic weights and isotopic compositions](https://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl?ele=&all=all&ascii=ascii2&isotype=all), alongside various helper functions and enumerations that can be used at runtime.

**input.h**: Provides the `input` namespace and the basic `input::keyword()` and `input::argument_line()` functions for the search of keywords/values in the `std::cin` and of flags/values in the `argv` list of input parameters, respectively.

**math.h**: Provides the `math` namespace and various routines and types to handle special math functions, constants, quadratures, interpolation etc. It serves mostly as a frontend for [GSL](https://www.gnu.org/software/gsl/).

**file.h**: Provides the `file` namespace, some helper functions, and the main types `file::Input` and `file::Output` for simplified reading and writing to disk files, respectively.

**timer.h**: Defines the array-like type `Timer<N>` to measure and store up to `N` elapsed time values between each consecutive calls of the member functions `Timer::start()` and `Timer::stop()`. In addition, it provides various helper member functions.

**mod.h**: Defines the `Mod` type for loading shared libraries (`*.so`) at runtime. Once instantiated, function pointers of type `T`, pointing to symbols from those libraries, can be retrieved using the `Mod::find_symbol<T>()` member function.

**pes.h**: Provides the `pes` namespace and the `pes::Frontend` type, which serves as a C++ abstraction over the user-defined potential energy surface (PES) routine. The user must implement the `void pes_startup()`, `f64 pes_value(f64 x[])`, and `void pes_shutdown()` functions, using whichever programming language is most convenient, and build them as a shared library, `*.so`. Then, the filename of the library can be used to instantiate an object of type `pes::Frontend`. For a given set of internuclear distances in atomic units (Bohr), say `x`, the PES value must be returned also in atomic units (Hartree). The `pes::Frontend` provides various helper member functions to manipulate the PES. Since PESs are traditionally implemented using the Fortran programming language, a [Fortran 90 wrapper](../templates/pes_wrapper.f90) for the used-defined routine is provided in the `catalyst/templates` directory.

**fgh.h**: Provides the `fgh` namespace, various helper functions and types, and the main function `fgh::matrix()` to build single and multichannel matrix representations of the [Fourier grid Hamiltonian](https://doi.org/10.1063/1.456888) (FGH) method.

**libblas.h**: Provides the `blas` namespace and a simpler, unified API to call functions of the legacy BLAS library from different implementors. Typical examples of backends are the [Intel Math Kernel Library](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html#gs.fg2j5m) (MKL) and [LAPACK](https://www.netlib.org/lapack/). The default case is the CBLAS version distributed alongside [GSL](https://www.gnu.org/software/gsl/). This module only regards host-side implementations of BLAS and a GPU-based version is provided in a separate module (see below).

**liblapack.h**: Provides the `lapack` namespace, and serves the same purpose as the `libblas.h` module but for the legacy [LAPACK](https://www.netlib.org/lapack/) library. If no backend library is used, then a partial LAPACK API is emulated using the GSL linear algebra module.

**libcuda.h**: Provides the `cuda` and `cuda::blas` namespaces alongside safe wrappers over the [CUDA](https://developer.nvidia.com/cuda-zone#) API. In particular, it defines the array-like type `Dev<T>` which handles dynamically allocated buffers of type `T` in device memory and the `cuda::blas::Frontend` type to manage BLAS functions executing on GPUs, using the [cuBLAS](https://developer.nvidia.com/cublas) backend library.

**numerov.h**: Provides the `numerov` namespace and implements various algorithms and types based on the [renormalized Numerov method](http://dx.doi.org/10.1063/1.436421) to integrate single and multichannel Schrodinger equations, and to compute closely related quantities such as reactance matrix, scattering matrix, and evaluation of bound states.

**struct.h**: Defines the `Struct` type, which stores an arbitrary number of members contiguously in memory. New members of type `T` can be added using `Struct::push_member<T>()` and later dereferenced with `Struct::dereference<T>()`. The `Struct` type allows easy serialization and de-serialization of complex data structures into/from a raw stream of bytes.
