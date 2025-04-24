set(sparseSolver_srcs
    linearSolver.cpp
    CGSolver.cpp
    PardisoSolver.cpp
    SPOOLESSolver.cpp
    invMKSolver.cpp
)
set(sparseSolver_hdrs
    CGSolver.h
    PardisoSolver.h
    SPOOLESSolver.h
    SPOOLESSolverMT.h
    invMKSolver.h
    linearSolver.h
    sparseSolverAvailability.h
    sparseSolvers.h
)

if (VegaFEM_BUILD_MODEL_REDUCTION)
  set(sparseSolver_srcs
      ${sparseSolver_srcs}
      ARPACKSolver.cpp
      invZTAZMSolver.cpp
      invZTAZSolver.cpp
      LagrangeMultiplierSolver.cpp
      ZTAZMultiplicator.cpp
  )
  set(sparseSolver_hdrs
      ${sparseSolver_hdrs}
      ARPACKSolver.h
      invZTAZMSolver.h
      invZTAZSolver.h
      LagrangeMultiplierSolver.h
      ZTAZMultiplicator.h
  )  
endif()

# Looks like building a shared lib here doesn't work, use static instead
# vega_add_library(sparseSolver
#   SOURCES ${sparseSolver_srcs}
#   PUBLIC_HEADERS ${sparseSolver_hdrs}
# )

add_library(sparseSolver STATIC ${sparseSolver_srcs})
target_include_directories(sparseSolver
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/vega>
    $<INSTALL_INTERFACE:include/vega/sparseSolver>
)

vega_install_library(sparseSolver)
install(FILES ${sparseSolver_hdrs}
    DESTINATION include/vega/sparseSolver
    COMPONENT Devel
)

target_compile_options(sparseSolver PRIVATE -fPIC)

target_link_libraries(sparseSolver
  PUBLIC
    sparseMatrix
    performanceCounter
)

if (VegaFEM_BUILD_MODEL_REDUCTION)
  target_link_libraries(sparseSolver
    PUBLIC
      ${INTEL_MKL_LIBRARIES}
      ${ARPACK_LIBRARIES}
      matrix
      # ${INTEL_MKL_LIBRARIES already included gfortran, why this one can not be removed}? Is it because ARPACK_LIBRARIES is a static lib?
      gfortran
  )
  
  # ADD_LIBRARY(arpack STATIC IMPORTED)
  # SET_TARGET_PROPERTIES(arpack PROPERTIES
  #     # IMPORTED_LOCATION ${ARPACK_LIBRARIES})
  #     IMPORTED_LOCATION /usr/local/ARPACK/libarpack_SUN4.a)
  #
  # target_link_libraries(sparseSolver
  #     PUBLIC
  #     arpack
  # )
endif()
