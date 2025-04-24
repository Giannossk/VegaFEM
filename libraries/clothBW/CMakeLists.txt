set(clothbw_sources
  clothBW.cpp
  clothBWFromObjMesh.cpp
)

set(clothbw_headers
  clothBW.h
  clothBWFromObjMesh.h
)

vega_add_library(clothBW
  SOURCES
    ${clothbw_sources}
  PUBLIC_HEADERS
    ${clothbw_headers}
)

target_link_libraries(clothBW
  PUBLIC
    objMesh
    minivector
    sparseMatrix
)
