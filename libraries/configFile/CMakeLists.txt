vega_add_library(configFile
  SOURCES
    configFile.cpp
  PUBLIC_HEADERS
    configFile.h
)

target_link_libraries(configFile
  PUBLIC
    minivector
)
