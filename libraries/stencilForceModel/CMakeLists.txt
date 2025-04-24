set(stencilForceModel_srcs
    clothBWStencilForceModel.cpp
    corotationalLinearFEMStencilForceModel.cpp
    forceModelAssembler.cpp
    isotropicHyperelasticFEMStencilForceModel.cpp
    linearFEMStencilForceModel.cpp
    massSpringStencilForceModel.cpp
    StVKStencilForceModel.cpp)

set(stencilForceModel_hdrs
    clothBWStencilForceModel.h
    corotationalLinearFEMStencilForceModel.h
    forceModelAssembler.h
    isotropicHyperelasticFEMStencilForceModel.h
    linearFEMStencilForceModel.h
    massSpringStencilForceModel.h
    stencilForceModel.h
    StVKStencilForceModel.h)

# if(VegaFEM_ENABLE_TBB_SUPPORT)
#   list(APPEND stencilForceModel_hdrs corotationalLinearFEMMT.h)
#   list(APPEND stencilForceModel_srcs corotationalLinearFEMMT.cpp)
# endif()

vega_add_library(stencilForceModel
  SOURCES
    ${stencilForceModel_srcs}
  PUBLIC_HEADERS
    ${stencilForceModel_hdrs}
)

target_link_libraries(stencilForceModel
  PUBLIC
    clothBW
    corotationalLinearFEM
    isotropicHyperelasticFEM
    massSpringSystem
    stvk
    forceModel
)

