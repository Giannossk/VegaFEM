find_path(ARPACK_INCLUDE_DIR
    argsym.h
    /usr/local/ARPACK/arpack++/include)

find_library(ARPACK_LIB arpack_SUN4
    /usr/local/ARPACK)

set(ARPACK_LIBRARIES ${ARPACK_LIB})
