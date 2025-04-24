
include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/objMesh
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/getopts
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/distanceField
)

add_executable(computeDistanceField computeDistanceField.cpp)
target_include_directories(displayObj
  PUBLIC
    ${GLUI_INCLUDE_DIRS}
)
target_link_libraries(computeDistanceField
  objMesh
  getopts
  distanceField 
  # ${OPENGL_gl_LIBRARY}
  # ${GLUT_glut_LIBRARY}
  # ${OPENGL_glu_LIBRARY}
  # ${GLUI_LIBRARY}
  # ${GLEW_LIBRARIES}
)
