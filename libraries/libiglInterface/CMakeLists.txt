vega_add_library(ligiglInterface
  SOURCES
    iglRemeshSelfIntersection.cpp
  PUBLIC_HEADERS
    iglRemeshSelfIntersection.h
)
target_link_libraries(ligiglInterface
  PUBLIC
    configFile
    ${IGL_LIBRARIES}
    ${CGAL_LIBRARIES}
)


