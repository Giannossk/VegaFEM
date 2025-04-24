
include_directories(
#     ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/objMesh
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/getopts
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/matrixIO
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/performanceCounter
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/lighting
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/glslPhong
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/camera
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/listIO
)

add_executable(displayObj displayObj.cpp)
target_include_directories(displayObj
  PUBLIC
    ${GLUI_INCLUDE_DIRS}
)
target_link_libraries(displayObj 
  objMesh
  getopts
  matrixIO
  performanceCounter
  lighting
  glslPhong
  camera
  listIO
  ${OPENGL_gl_LIBRARY} 
  ${GLUT_glut_LIBRARY} 
  ${OPENGL_glu_LIBRARY} 
  ${GLUI_LIBRARY} 
  ${GLEW_LIBRARIES})

add_executable(objMergeFiles objMergeFiles.cpp)
target_include_directories(objMergeFiles
  PUBLIC
    ${GLUI_INCLUDE_DIRS}
)
target_link_libraries(objMergeFiles 
  getopts
  objMesh 
  # imageIO
  # glslPhong
  # camera
  matrixIO 
  # lighting
  # configFile
  # loadList
  ${OPENGL_gl_LIBRARY} 
  ${GLUT_glut_LIBRARY} 
  ${OPENGL_glu_LIBRARY} 
  ${GLUI_LIBRARY} 
  ${GLEW_LIBRARIES})
