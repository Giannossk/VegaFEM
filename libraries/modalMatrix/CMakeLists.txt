vega_add_library(modalMatrix
  SOURCES
    modalMatrix.cpp
    modalMatrixTransposed.cpp
  PUBLIC_HEADERS
    modalMatrix.h
    modalMatrixTransposed.h
)
target_link_libraries(modalMatrix
  PUBLIC
    matrixIO
    ${LAPACK_LIBRARIES}
    ${BLAS_LIBRARY}
)

