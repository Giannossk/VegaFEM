/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Yijing Li                                *
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

#include "float.h"
#include "mat3d.h"
#include "volumetricMeshDeformationGradient.h"

namespace vega 
{

// computes the deformation gradient for the deformation given by the displacement vector u (length 3n, where n=#vertices), for the element with index "elementIndex"
// F is a 3x3 matrix, stored row-major into a vector of length 9
void VolumetricMeshDeformationGradient::ComputeDeformationGradient(VolumetricMesh * mesh, double * u, int elementIndex, double * F)
{
  Vec3d centroid = mesh->getElementCenter(elementIndex);
  const int numFields = 1;
  mesh->interpolateGradient(elementIndex, u, numFields, centroid, F);

  F[0] += 1.0;
  F[4] += 1.0;
  F[8] += 1.0;
}

// computes the three principal stretches (singular values of F)
int VolumetricMeshDeformationGradient::ComputePrincipalStretches(double * F_, double * lambda)
{
  // perform modified SVD on the deformation gradient
  Mat3d F(F_);
  Mat3d U;
  Mat3d V;
  Vec3d Lambda;
  int modifiedSVD = 1;
  if (SVD(F, U, Lambda, V, modifiedSVD) != 0)
  {
    printf("Error in diagonalization\n");
    return 1;
  }

  /*
    SVD for the deformation gradient has now been computed.
    It is available in U, Lambda, V
  */

  Lambda.convertToArray(lambda);

  return 0;
}

// maximal stretch in the entire mesh
double VolumetricMeshDeformationGradient::ComputeMaximalStretch(VolumetricMesh * mesh, double * u)
{
  int numElements = mesh->getNumElements();
  double maxLambda = -DBL_MAX;

  for(int el=0; el<numElements; el++)
  {
    double F[9];
    double lambda[3] = { 0, 0, 0 };
    ComputeDeformationGradient(mesh, u, el, F);
    ComputePrincipalStretches(F, lambda);
    if (lambda[0] > maxLambda)
      maxLambda = lambda[0];
  }

  return maxLambda;
}



} // namespace vega
