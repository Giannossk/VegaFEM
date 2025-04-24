set(mesh_src
    boundingBox.cpp
    createTriMesh.cpp
    exactOctree.cpp
    geometryQuery.cpp
    intersection_tunicate.cpp
    labelOuterTets.cpp
    meshIntersection.cpp
    predicates.cpp
    predicates_Shewchuk.c
    rectKey.cpp
    simpleSphere.cpp
    tetKey.cpp
    tetMeshGeo.cpp
    tetMeshManifold.cpp
    tetrahedron.cpp
    triangle.cpp
    tribox3.cpp
    triKey.cpp
    triMeshGeo.cpp
    triMeshManifold.cpp
    triMeshNeighbor.cpp
    triMeshPseudoNormal.cpp
    verticesInfo.cpp
    windingNumberTree.cpp
)

set(mesh_hdr
    boundingBox.h
    createTriMesh.h
    edgeKey.h
    exactOctree.h
    geometryQuery.h
    halfSpace.h
    initPredicates.h
    labelOuterTets.h
    meshIntersection.h
    plane.h
    predicates.h
    rectKey.h
    simpleSphere.h
    tetKey.h
    tetMeshGeo.h
    tetMeshManifold.h
    tetrahedron.h
    triangle.h
    tribox3.h
    triKey.h
    triMeshGeo.h
    triMeshManifold.h
    triMeshNeighbor.h
    triMeshPseudoNormal.h
    verticesInfo.h
    windingNumberTree.h
)

if (VegaFEM_ENABLE_OpenGL_SUPPORT)
    set(mesh_src
        ${mesh_src}
        # triangle.cpp
        # boundingBox.cpp
        # exactOctree.cpp
        # tetMeshGeo.cpp
        # labelOuterTets.cpp
        # meshIntersection.cpp
        # simpleSphere.cpp
        # windingNumberTree.cpp
    )
    set(mesh_hdr
        ${mesh_hdr}
        # triangle.h
        # boundingBox.h
        # exactOctree.h
        # tetMeshGeo.h
        # labelOuterTets.h
        # meshIntersection.h
        # simpleSphere.h
        # windingNumberTree.h
    )
endif()

vega_add_library(mesh
  SOURCES 
    ${mesh_src}
  PUBLIC_HEADERS 
    ${mesh_hdr}
)

target_link_libraries(mesh
  PUBLIC
    minivector
    basicAlgorithms
    # windingNumber
)

if (VegaFEM_ENABLE_OpenGL_SUPPORT)
  target_link_libraries(mesh
    PUBLIC
      ${OPENGL_gl_LIBRARY}
      ${OPENGL_glu_LIBRARY}
      openGLHelper
  )
endif()
