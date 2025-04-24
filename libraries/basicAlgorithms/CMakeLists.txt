file(GLOB_RECURSE basicAlgorithms_sources "*.cpp")
file(GLOB_RECURSE basicAlgorithms_headers "*.h")

vega_add_library(basicAlgorithms
  SOURCES 
  	${basicAlgorithms_sources}
  PUBLIC_HEADERS
    ${basicAlgorithms_headers}
)
