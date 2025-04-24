# FindwxWidgets
find_package(wxWidgets COMPONENTS gl core base)

if(wxWidgets_FOUND)
  include_directories(${wxWidgets_INCLUDE_DIRS})

  set(LARGE_MODAL_DEF_SRCS 
      cubicPolynomials.cpp 
      fixedVertices.cpp 
      frequencies.cpp 
      largeModalDeformationFactory.cpp 
      linearModes.cpp 
      main.cpp 
      nonlinearModes.cpp 
      view.cpp 
      renderingMesh.cpp 
      simulationMesh.cpp 
      canvas.cpp 
      modalDerivatives.cpp 
      sketch.cpp 
      interpolate.cpp 
      convert.cpp 
      runtime.cpp 
   )

  add_executable(largeModalDeformationFactory ${LARGE_MODAL_DEF_SRCS})

  target_compile_definitions(largeModalDeformationFactory
      PRIVATE
      ${wxWidgets_DEFINITIONS} )

  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${wxWidgets_CXX_FLAGS}")
  target_compile_options(largeModalDeformationFactory PRIVATE ${wxWidgets_CXX_FLAGS})

  set(wx_extra_lib )
  target_link_libraries(largeModalDeformationFactory 
      reducedStvk 
      stvk 
      reducedElasticForceModel 
      reducedForceModel 
      forceModel 
      renderVolumetricMesh 
      sparseSolver 
      sparseMatrix 
      volumetricMesh 
      objMesh 
      imageIO 
      modalMatrix 
      matrix 
      matrixIO 
      getopts 
      camera 
      minivector 
      listIO
      openGLHelper
      ${INTEL_MKL_LIBRARIES}
      ${CMAKE_THREAD_LIBS_INIT}
      ${OPENGL_gl_LIBRARY} 
      ${GLUT_glut_LIBRARY} 
      ${OPENGL_glu_LIBRARY} 
      ${GLUI_LIBRARY}
      ${wxWidgets_LIBRARIES}
      )
  endif(wxWidgets_FOUND)
