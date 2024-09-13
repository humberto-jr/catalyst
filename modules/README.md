# modules

## About

A collection of lightweight modules that wraps the boilerplate code required for calling the C/C++ standard library and third-party code. These would encapsulate type conversions, enforce const correctness, internal state management, error handling, thread safety, message passing, I/O, GPU usage and synchronization, algorithms, math, coding conventions, etc. While it is intended to provide a clean, more readable and safe API, it should not become a barrier to accessing a lower-level API for the sake of, say, performance.

## Content

**libc.h**: The most fundamental module, which is included by everything else and provides all header files from the C standard library. It also includes the POSIX `unistd.h` header.

**types.h**: Provides immutable and mutable primitive type aliases using a modern naming convention and some utility functions. The immutable unsigned integers are `byte`, `u8`, `u16`, `u32`, `u64`, and `usize`; the immutable signed integers are `s8`, `s16`, `s32`, and `s64`; the immutable floating points are `f32`, `f64`, and `f128`; and the immutable complex floating points are `c32`, `c64`, and `c128`. The C literal string is renamed as `c_str`. The mutable type `T` is defined as `mut<T>`.

**print.h**: Provides the `print` namespace and the basic thread-safe functions `print::line()` and `print::error()` to write the `stdout` and `stderr` without the somewhat cumbersome use of C++ `std::cout` or the error-prone formattings of C `printf()`.

**vector.h**: Defines `vec<T>`, an overly simple and lightweight dynamically allocated vector of type `T`.

**string.h**: Defines the primitive type `str = vec<char>` and `string = str` for dynamically allocated strings, in addition to various text formatting and management functions.

**matrix.h**: Defines `mat<T>`, a lightweight matrix abstraction built on top of `vec<T>`. This module does not include linear algebra operations just yet.

**essentials.h**: For convenience, it includes the previous header files and the `omp.h` from the [OpenMP](https://www.openmp.org/) library (OMP) for threading usage. It also defines the global `MAX_HOST_THREAD_COUNT` constant and the `thread_count()` and `thread_id()` runtime functions.

**libgsl.h**: Includes all relevant [GSL](https://www.gnu.org/software/gsl/) header files used throughout the codebase. More headers are added on demand.

**libmpi.h**: Provides the `mpi` namespace, some helper functions, and the `mpi::frontend` type, which wraps MPI-related internal states and functionalities of a given [Message Passing Interface](https://www.mpi-forum.org/) backend library. It uses C++ function overloading and type inference to alleviate the use of the original MPI API. If an MPI backend is not used, the API provided by this module becomes a collection of dummy no-op calls. Thus, higher-level codes won't need to be changed.

**nist.h**: Provides the `nist` namespace, and serves as a database for all relevant [NIST fundamental physical constants](https://pml.nist.gov/cuu/Constants/Table/allascii.txt), [NIST atomic weights and isotopic compositions](https://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl?ele=&all=all&ascii=ascii2&isotype=all), alongside various helper functions and enumerations that can be used at runtime.
