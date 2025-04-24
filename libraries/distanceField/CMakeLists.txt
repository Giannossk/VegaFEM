file(GLOB_RECURSE distanceField_sources 
  closestPointField.cpp
  distanceField.cpp
  distanceFieldBase.cpp
  distanceFieldCreator.cpp
  distanceFieldNarrowBand.cpp
  marchingCubes.cpp
  signedDistanceFieldFromPolygonSoup.cpp
)

file(GLOB_RECURSE distanceField_headers "*.h")

vega_add_library(distanceField
  SOURCES
    ${distanceField_sources}
  PUBLIC_HEADERS
    ${distanceField_headers}
)

target_link_libraries(distanceField
  PUBLIC
    objMesh 
    mesh 
    hashTable 
    minivector 
    performanceCounter 
    matrixIO
    configFile
    basicAlgorithms
)
