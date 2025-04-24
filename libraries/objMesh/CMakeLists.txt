set(OBJ_SRCS
  objMesh.cpp
  objMeshBinaryLoader.cpp
  objMeshGraph.cpp
  objMeshOrientable.cpp
  createObjMesh.cpp
  objMeshClose.cpp
)
set(OBJ_HDRS
  objMesh.h
  objMeshBinaryLoader.h
  objMeshGraph.h
  objMeshOrientable.h
  createObjMesh.h
  objMeshClose.h
)
if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  set(OBJ_SRCS
    ${OBJ_SRCS}
    octree.cpp
    objMeshOctree.cpp
    objMeshOffsetVoxels.cpp
    objMeshRender.cpp
  )
  set(OBJ_HDRS
    ${OBJ_HDRS}
    octree.h
    objMeshOctree.h
    objMeshOffsetVoxels.h
    objMeshRender.h
  )
endif()

vega_add_library(objMesh
  SOURCES ${OBJ_SRCS}
  PUBLIC_HEADERS ${OBJ_HDRS}
)
target_link_libraries(objMesh
  PUBLIC
    minivector
    matrixIO
    imageIO
    sparseMatrix
    graph
    basicAlgorithms
    mesh
    # openGLHelper
)
if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  target_link_libraries(objMesh
    PUBLIC
      ${OPENGL_gl_LIBRARY}
      ${OPENGL_glu_LIBRARY}
      openGLHelper
  )
endif()
