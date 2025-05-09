set(matrix_srcs
  matrixProjection.cpp
  matrixPCA.cpp
  matrixBLAS.cpp
  matrixLAPACK.cpp
  matrixBLASOptimized.cpp
  matrix.cpp
)
set(matrix_hdrs
    expokit_xgpadm.h
    matrix.h
    matrixBLAS.h
    matrixLAPACK.h
    matrixPCA.h
    matrixProjection.h
)
if (VegaFEM_ENABLE_ExpoKit_SUPPORT)
  set(matrix_srcs
    ${matrix_srcs}
    matrixExp.cpp
  )
  set(matrix_hdrs
    ${matrix_hdrs}
    matrixExp.h
  )
endif()

vega_add_library(matrix
  SOURCES
    ${matrix_srcs}
  PUBLIC_HEADERS
    ${matrix_hdrs}
)

target_compile_options(matrix PUBLIC -Wl,--no-as-needed -m64)

target_link_libraries(matrix
  PUBLIC
    matrixIO
    ${INTEL_MKL_LIBRARIES}
    ${BLAS}
    ${CBLAS_LIBRARY}
    ${LAPACK_LIBRARIES}
)
