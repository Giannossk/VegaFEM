vega_add_library(interpolationCoordinates
  SOURCES
    barycentricCoordinates.cpp
  PUBLIC_HEADERS
    interpolationCoordinates.h 
    barycentricCoordinates.h
)

target_link_libraries(interpolationCoordinates
  PUBLIC
    minivector
    objMesh
    volumetricMesh
    mesh
    sparseMatrix
)
