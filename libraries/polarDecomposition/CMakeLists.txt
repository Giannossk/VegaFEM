vega_add_library(polarDecomposition
  SOURCES
    polarDecomposition.cpp
    polarDecompositionGradient.cpp
  PUBLIC_HEADERS
    polarDecomposition.h
    polarDecompositionGradient.h
)
target_link_libraries(polarDecomposition
  PUBLIC
    minivector
)

