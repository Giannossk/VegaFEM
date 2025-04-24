vega_add_library(lighting
  SOURCES
    cameraLighting.cpp
    lighting.cpp
  PUBLIC_HEADERS
    cameraLighting.h
    lighting.h
)

target_link_libraries(lighting
  PUBLIC
    configFile
    camera
    ${OPENGL_LIBRARIES}
)

