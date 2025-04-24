project(VegaFEM)

set(VegaFEM_VERSION 4.0)

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
  cmake_policy(SET CMP0079 NEW)
  cmake_policy(SET CMP0072 OLD)
  if (POLICY CMP0022)
    # Use INTERFACE_LINK_LIBRARIES when available.
    cmake_policy(SET CMP0022 NEW)
  endif()
  if (POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW)
  endif()
endif(COMMAND CMAKE_POLICY)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
include(VegaFEMMacros)

# Add Options
option(VegaFEM_BUILD_UTILITIES "Build utility classes in addition to libraries." ON)

option(VegaFEM_BUILD_MODEL_REDUCTION "Build model-reduction" ON)

option(VegaFEM_BUILD_IMMERSION_MESHER "Build immersion-mesher" OFF)

option(VegaFEM_BUILD_RIGID_BODIES "Build Rigid body support" OFF)

option(VegaFEM_ENABLE_OpenGL_SUPPORT "Should modules that require OpenGL be enabled?" ON)

option(VegaFEM_ENABLE_ExpoKit_SUPPORT "Should matrix classes use ExpoKit for exponentiation?" OFF)
# TODO: define USE_EXPOKIT if enabled

option(VegaFEM_ENABLE_CLOTH_SUPPORT "Should modules that require OpenGL be enabled?" ON)


if (VegaFEM_ENABLE_OpenGL_SUPPORT)
    add_definitions( -DENABLE_OpenGL )
endif()

if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  # Only add Cg support if OpenGL is turned on. This may change in the future.
  option(VegaFEM_ENABLE_Cg_SUPPORT "Should modules that require Cg be enabled?" ON)
endif()

if(NOT VegaFEM_ENABLE_OpenGL_SUPPORT)
    set(VegaFEM_BUILD_UTILITIES OFF CACHE STRING "utilities cannot be build without OPENGL" FORCE)
endif()

if (VegaFEM_ENABLE_OpenGL_SUPPORT AND VegaFEM_BUILD_UTILITIES)
  find_package(GLUI)
  if(NOT GLUI_FOUND)
    add_subdirectory(libraries/glui/glui-2.35/src)
    set(GLUI_LIBRARY glui)
    set(GLUI_INCLUDE_DIR) # Empty this as library will export its own includes.
  endif()
endif()

set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH/INSTALL_NAME_DIR to be used when installing
if (NOT APPLE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:\$ORIGIN/../lib")
endif(NOT APPLE)
# On OSX, we need to set INSTALL_NAME_DIR instead of RPATH
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_INSTALL_NAME_DIR
set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH which point to
# directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  find_package(GLEW REQUIRED)

  include_directories(${OPENGL_INCLUDE_DIR})
  include_directories(${GLUT_INCLUDE_DIR})
  include_directories(${GLEW_INCLUDE_DIR})

  if (GLUT_FOUND AND APPLE)
    mark_as_advanced(GLUT_cocoa_LIBRARY)
  endif()

  if (VegaFEM_ENABLE_Cg_SUPPORT)
    find_package(Cg REQUIRED)
    mark_as_advanced(
      CG_COMPILER
      CG_GL_LIBRARY
      CG_INCLUDE_PATH
      CG_LIBRARY
    )
  endif()
endif()

if (VegaFEM_BUILD_MODEL_REDUCTION)
  if (NOT APPLE)
    find_package(MKL)
    if(MKL_FOUND)
      set(BLA_VENDOR "Intel mkl")
      include_directories(${INTEL_MKL_INCLUDE_DIR})
      # TODO: set option for the paradiso solvers and define PARDISO_SOLVER_IS_AVAILABLE
      add_definitions( -DPARDISO_SOLVER_IS_AVAILABLE)
    else()
      find_package(LAPACKE REQUIRED) # Also searches for cblas
      find_package(LAPACK REQUIRED)
      # find_package(CBLAS REQUIRED)
      find_package(BLAS REQUIRED)
      include_directories(${LAPACKE_INCLUDE_DIR})
      include_directories(${LAPACK_INCLUDE_DIR})
      include_directories(${CBLAS_INCLUDE_DIR})
      include_directories(${BLAS_INCLUDE_DIR})
    endif()

    find_package(ARPACK REQUIRED)
    include_directories(${ARPACK_INCLUDE_DIR})
  endif()
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries/include)

set(VegaFEM_Modules
  basicAlgorithms
  clothBW
  configFile
  constrainedDOFs
  corotationalLinearFEM
  distanceField
  elasticForceModel
  forceModel
  getopts
  graph
  hashTable
  imageIO
  integrator
  integratorSparse
  interpolationCoordinates
  isotropicHyperelasticFEM
  laplacianMatrix
  listIO
  massSpringSystem
  # matrix
  matrixIO
  mesh
  minivector
  objMesh
  # openGLHelper
  performanceCounter
  polarDecomposition
  quaternion
  # shapeEdit
  sparseMatrix
  sparseSolver
  stencilForceModel
  stvk
  volumetricMesh
  windingNumber
)

# include_directories(include)

if (VegaFEM_BUILD_MODEL_REDUCTION)
  set(VegaFEM_Modules
    ${VegaFEM_Modules}
    integratorDense
    matrix
    modalMatrix
    reducedElasticForceModel
    reducedForceModel
    reducedStvk
    shapeEdit
  )
endif()

if (VegaFEM_BUILD_IMMERSION_MESHER)
    set(VegaFEM_Modules
      ${VegaFEM_Modules}
      mesher
      immersionMesher
      virtualTets
      libiglInterface
      exactArithmetic
    )
endif()

if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  set(VegaFEM_Modules
    ${VegaFEM_Modules}
    animationHelper
    camera
    glslPhong
    lighting
    openGLHelper
    sceneObject
  )
  if (VegaFEM_ENABLE_Cg_SUPPORT)
    set(VegaFEM_Modules
      ${VegaFEM_Modules}
      objMeshGPUDeformer
    )
  endif()
  if (VegaFEM_BUILD_MODEL_REDUCTION)
    set(VegaFEM_Modules
      ${VegaFEM_Modules}
      sceneObjectReduced
      renderVolumetricMesh
    )
  endif()
endif()



add_subdirectory(libraries)

if(VegaFEM_BUILD_UTILITIES)
  add_subdirectory(utilities)
endif(VegaFEM_BUILD_UTILITIES)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/VegaFEMConfigVersion.cmake"
  VERSION ${VegaFEM_VERSION}
  COMPATIBILITY AnyNewerVersion
)


export(PACKAGE VegaFEM)

export(TARGETS ${VegaFEM_Modules}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/VegaFEM/VegaFEMTargets.cmake"
  NAMESPACE VegaFEM::
)

# export(EXPORT VegaFEMTargets
#   FILE "${CMAKE_CURRENT_BINARY_DIR}/VegaFEMTargets.cmake"
#   NAMESPACE VegaFEM::
# )

configure_file(
  CMake/VegaFEMConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/VegaFEMConfig.cmake"
  @ONLY
)

# Install step

set(ConfigPackageLocation lib/cmake/VegaFEM)
install(EXPORT VegaFEMTargets
  FILE VegaFEMTargets.cmake
  NAMESPACE VegaFEM::
  DESTINATION ${ConfigPackageLocation}
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/VegaFEMConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/VegaFEMConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)


