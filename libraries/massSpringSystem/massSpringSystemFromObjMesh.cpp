/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "massSpringSystem" library, Copyright (C) 2007 CMU, 2009 MIT,         *
 *                                           2018 USC                    *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Daniel Schroeder                         *
 * http://www.jernejbarbic.com/vega                                      *
 *                                                                       *
 * Research: Jernej Barbic, Hongyi Xu, Yijing Li,                        *
 *           Danyong Zhao, Bohan Wang,                                   *
 *           Fun Shing Sin, Daniel Schroeder,                            *
 *           Doug L. James, Jovan Popovic                                *
 *                                                                       *
 * Funding: National Science Foundation, Link Foundation,                *
 *          Singapore-MIT GAMBIT Game Lab,                               *
 *          Zumberge Research and Innovation Fund at USC,                *
 *          Sloan Foundation, Okawa Foundation,                          *
 *          USC Annenberg Foundation                                     *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of the BSD-style license that is            *
 * included with this library in the file LICENSE.txt                    *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the file     *
 * LICENSE.TXT for more details.                                         *
 *                                                                       *
 *************************************************************************/

#include "objMesh.h"
#include "massSpringSystemFromObjMesh.h"

namespace vega 
{

int MassSpringSystemFromObjMesh::GenerateMassSpringSystem(ObjMesh * quadMesh, MassSpringSystem ** massSpringSystem, double surfaceDensity, double tensileStiffness, double shearStiffness, double bendStiffness, double damping, int addGravity)
{
  if (!quadMesh->isQuadrilateralMesh())
  {
    printf("Error: mesh is not quadrilateral.\n");
    return 1;
  }

  int numParticles;
  double * restPositions;
  int numQuads;
  int * faceCardinalities;
  int * quads;

  quadMesh->exportFaceGeometry(&numParticles, &restPositions, &numQuads, &faceCardinalities, &quads);

  *massSpringSystem = new MassSpringSystem(numParticles, restPositions, numQuads, quads, surfaceDensity, tensileStiffness, shearStiffness, bendStiffness, damping, addGravity);

  free(quads);
  free(faceCardinalities);
  free(restPositions);

  return 0;
}

} // namespace vega
