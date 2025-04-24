vega_add_library(performanceCounter
  SOURCES
    profiler.cpp
  PUBLIC_HEADERS
    performanceCounter.h
    frameRateLock.h
    profiler.cpp
    profiler.h
    stopWatch.h
)

target_link_libraries(performanceCounter
  PUBLIC
    basicAlgorithms
    matrixIO
)
