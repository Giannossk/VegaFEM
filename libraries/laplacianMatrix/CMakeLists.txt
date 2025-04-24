vega_add_library(laplacianMatrix
  SOURCES
    laplacianMatrix.cpp
  PUBLIC_HEADERS
    laplacianMatrix.h
)
target_link_libraries(laplacianMatrix
  PUBLIC
    sparseMatrix 
    volumetricMesh 
    # minivector
    sparseSolver
)
