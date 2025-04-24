vega_add_library(shapeEdit
  SOURCES
    arapDeformer.cpp
    generateLaplacian.cpp
  PUBLIC_HEADERS
    arapDeformer.h
    generateLaplacian.h
)

target_link_libraries(shapeEdit
  PUBLIC
    sparseMatrix
    objMesh
    sparseSolver
    volumetricMesh
    polarDecomposition
)
