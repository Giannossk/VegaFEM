vega_add_library(mesher
  SOURCES
    delaunayMesher.cpp
    isosurfaceMesher.cpp
    tetMesher.cpp
    triangleTetIntersection.cpp
  PUBLIC_HEADERS
    delaunayMesher.h
    isosurfaceMesher.h
    tetMesher.h
    triangleTetIntersection.h
)

target_link_libraries(mesher
  PUBLIC
    minivector
    objMesh
    mesh
    windingNumber
    distanceField
    matrixIO
    performanceCounter
    volumetricMesh
)
