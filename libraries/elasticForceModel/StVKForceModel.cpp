/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "forceModel" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC     *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Jernej Barbic                                            *
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

#include "StVKForceModel.h"

namespace vega 
{

StVKForceModel::StVKForceModel(StVKInternalForces * stVKInternalForces_, StVKStiffnessMatrix * stVKStiffnessMatrix_): stVKInternalForces(stVKInternalForces_), stVKStiffnessMatrix(stVKStiffnessMatrix_)
{
  r = 3 * stVKInternalForces->GetVolumetricMesh()->getNumVertices();
  ownStiffnessMatrix = false;
  if (stVKStiffnessMatrix == NULL)
  {
    stVKStiffnessMatrix = new StVKStiffnessMatrix(stVKInternalForces);
    ownStiffnessMatrix = true;
  }
}

StVKForceModel::~StVKForceModel()
{
  if (ownStiffnessMatrix)
    delete(stVKStiffnessMatrix);
}

double StVKForceModel::GetElasticEnergy(const double * u)
{
  return stVKInternalForces->ComputeEnergy(u);
}

void StVKForceModel::GetInternalForce(const double * u, double * internalForces)
{
  stVKInternalForces->ComputeForces(u, internalForces);
}

void StVKForceModel::GetTangentStiffnessMatrixTopology(SparseMatrix ** tangentStiffnessMatrix)
{
  stVKStiffnessMatrix->GetStiffnessMatrixTopology(tangentStiffnessMatrix);
}

void StVKForceModel::GetTangentStiffnessMatrix(const double * u, SparseMatrix * tangentStiffnessMatrix)
{
  stVKStiffnessMatrix->ComputeStiffnessMatrix(u, tangentStiffnessMatrix);
} 


} // namespace vega
