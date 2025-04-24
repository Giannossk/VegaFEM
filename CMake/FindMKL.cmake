#

# INTEL_MKL_INCLUDE_DIR - where to find autopack.h
# MKLSOLVER_LIBRARIES   - List of fully qualified libraries to link against.
# MKLSOLVER_FOUND       - Do not attempt to use if "no" or undefined.

set(INTEL_MKL_YEAR 2020)
set(INTEL_MKL_ARCH intel64)
find_path(INTEL_MKL_INCLUDE_DIR 
  mkl_blas.h
  "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/include"
  /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/include
)

# set(LIB_MKL_LIST mkl_intel_ilp64 mkl_intel_thread mkl_core mkl_solver_ilp64 mkl_mc mkl_mc3 mkl_lapack PTHREAD mkl_p4n iomp5)

find_library(MKL_INTEL_LP64 mkl_intel_lp64
  "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/lib/${INTEL_MKL_ARCH}"
  /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/lib/${INTEL_MKL_ARCH}
)

# if(CMAKE_COMPILER_IS_GNUCXX )
#     find_library(MKL_THREAD mkl_gnu_thread
#     "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/lib/${INTEL_MKL_ARCH}"
#     /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/lib/${INTEL_MKL_ARCH}
#     )
# else(CMAKE_COMPILER_IS_GNUCXX )
#     find_library(MKL_THREAD mkl_intel_thread
#     "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/lib/${INTEL_MKL_ARCH}"
#     /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/lib/${INTEL_MKL_ARCH}
#     )
# endif(CMAKE_COMPILER_IS_GNUCXX )

find_library(MKL_THREAD mkl_intel_thread
    "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/lib/${INTEL_MKL_ARCH}"
    /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/lib/${INTEL_MKL_ARCH}
)

find_library(MKL_CORE mkl_core
  "C:/Program Files/Intel/ComposerXE-${INTEL_MKL_YEAR}/mkl/lib/${INTEL_MKL_ARCH}"
  /opt/intel/compilers_and_libraries_${INTEL_MKL_YEAR}/linux/mkl/lib/${INTEL_MKL_ARCH}
)

set(INTEL_MKL_LIBRARIES m ${MKL_INTEL_LP64} ${MKL_THREAD} ${MKL_CORE} iomp5 gfortran)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL
  REQUIRED_VARS
    INTEL_MKL_INCLUDE_DIR
    MKL_INTEL_LP64
    MKL_THREAD 
    MKL_CORE 
    )
    
mark_as_advanced(
    INTEL_MKL_INCLUDE_DIR
    MKL_INTEL_LP64
    MKL_THREAD 
    MKL_CORE 
)
