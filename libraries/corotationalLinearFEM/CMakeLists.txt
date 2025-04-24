set(corotationallinearfem_sources
    corotationalLinearFEM.cpp)

set(corotationallinearfem_headers
    corotationalLinearFEM.h)

vega_add_library(corotationalLinearFEM
  SOURCES
    ${corotationallinearfem_sources}
  PUBLIC_HEADERS
    ${corotationallinearfem_headers}
)

target_link_libraries(corotationalLinearFEM
  PUBLIC
    polarDecomposition
    volumetricMesh
    sparseMatrix
  INTERFACE
    minivector
)
