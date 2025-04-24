file(GLOB_RECURSE EA_sources 
  er.cpp
  # er_toDouble.cpp
  planeER.cpp
  vec3ER.cpp
)
file(GLOB_RECURSE EA_headers 
  er.h
  planeER.h
  vec3ER.h
)

vega_add_library(exactArithmetic
  SOURCES 
  	${EA_sources}
  PUBLIC_HEADERS
    ${EA_headers}
)
