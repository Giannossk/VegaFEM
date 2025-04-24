include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/minivector
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/objMesh
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/matrixIO
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/getopts
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sparseMatrix
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/volumetricMesh
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/listIO
   ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/include
)

set(VOLUTILS_LIBS 
    minivector 
    volumetricMesh 
    listIO 
    objMesh 
    matrixIO 
    getopts 
    sparseMatrix)

set(VOLUTILS_LIBS ${VOLUTILS_LIBS} ${SPOOLES_LIBRARY} ${PARDISO_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

add_executable(generateMassMatrix generateMassMatrix.cpp)
target_link_libraries(generateMassMatrix ${VOLUTILS_LIBS})
add_executable(generateInterpolant generateInterpolant.cpp)
target_link_libraries(generateInterpolant ${VOLUTILS_LIBS})
add_executable(generateInterpolationMatrix generateInterpolationMatrix.cpp)
target_link_libraries(generateInterpolationMatrix ${VOLUTILS_LIBS})
add_executable(generateSurfaceMesh generateSurfaceMesh.cpp)
target_link_libraries(generateSurfaceMesh ${VOLUTILS_LIBS})
