vega_add_library(reducedElasticForceModel
  SOURCES
    reducedLinearForceModel.cpp
    reducedLinearStVKForceModel.cpp
    reducedMassSpringSystemForceModel.cpp
    reducedMassSpringSystemForceModelWithHessian.cpp
    reducedSpringForceModel.cpp
    reducedStVKForceModel.cpp
    reducedStVKForceModelWithHessian.cpp
    reducedSubspaceStVKForceModel.cpp
  PUBLIC_HEADERS
    reducedLinearForceModel.h
    reducedLinearStVKForceModel.h
    reducedMassSpringSystemForceModel.h
    reducedMassSpringSystemForceModelWithHessian.h
    reducedSpringForceModel.h
    reducedStVKForceModel.h
    reducedStVKForceModelWithHessian.h
    reducedSubspaceStVKForceModel.h
)
target_link_libraries(reducedElasticForceModel
  PUBLIC
    reducedForceModel
    reducedStvk
    stvk
    massSpringSystem
    performanceCounter
    # modalMatrix
    # sparseMatrix
)

