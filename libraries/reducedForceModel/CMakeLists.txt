vega_add_library(reducedForceModel
  SOURCES
    reducedForceModel.cpp
    reducedForceModelWithHessian.cpp
  PUBLIC_HEADERS
    reducedForceModel.h
    reducedForceModelWithHessian.h
)
target_link_libraries(reducedForceModel
  PUBLIC
#     ${LAPACK_LIBRARIES}
#     ${BLAS_LIBRARIES}
    modalMatrix
)
