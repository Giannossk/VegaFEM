vega_add_library(integrator
  SOURCES
    integratorBase.cpp
    getIntegratorSolver.cpp
  PUBLIC_HEADERS
    integratorBase.h 
    getIntegratorSolver.h 
    integratorSolverSelection.h
)
target_include_directories(integrator
  PUBLIC
    ${PARDISO_INCLUDE_DIRS}
)
target_link_libraries(integrator
  PUBLIC
    performanceCounter
    sparseSolver
    forceModel
  INTERFACE
    sparseMatrix
)
