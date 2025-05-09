/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "integrator" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC     *
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "integratorBaseSparse.h"

namespace vega 
{

IntegratorBaseSparse::IntegratorBaseSparse(int r, double timestep, SparseMatrix * massMatrix_, ForceModel * forceModel_, int numConstrainedDOFs_, int * constrainedDOFs_, double dampingMassCoef, double dampingStiffnessCoef): IntegratorBase(r, timestep, dampingMassCoef, dampingStiffnessCoef), massMatrix(massMatrix_), forceModel(forceModel_), numConstrainedDOFs(numConstrainedDOFs_)
{
  systemSolveTime = 0.0;
  forceAssemblyTime = 0.0;

  constrainedDOFs = (int*) malloc (sizeof(int) * numConstrainedDOFs);
  memcpy(constrainedDOFs, constrainedDOFs_, sizeof(int) * numConstrainedDOFs);

  ownDampingMatrix = 1;
  SparseMatrixOutline outline(r);
  dampingMatrix = new SparseMatrix(&outline);

  tangentStiffnessMatrixOffset = NULL;
}

IntegratorBaseSparse::~IntegratorBaseSparse()
{
  free(constrainedDOFs);
  if (ownDampingMatrix)
    delete(dampingMatrix);
  delete(tangentStiffnessMatrixOffset);
}

void IntegratorBaseSparse::SetDampingMatrix(SparseMatrix * dampingMatrix_)
{
  if (ownDampingMatrix)
    delete(dampingMatrix);

  dampingMatrix = dampingMatrix_;
  ownDampingMatrix = 0;
}

double IntegratorBaseSparse::GetKineticEnergy()
{
  return 0.5 * massMatrix->QuadraticForm(qvel);
}

double IntegratorBaseSparse::GetTotalMass()
{
  return massMatrix->SumEntries();
}

void IntegratorBaseSparse::SetTangentStiffnessMatrixOffset(SparseMatrix * tangentStiffnessMatrixOffset_, int reuseTopology)
{
  if (reuseTopology && (tangentStiffnessMatrixOffset != NULL))
    *tangentStiffnessMatrixOffset = *tangentStiffnessMatrixOffset_;
  else
  {
    delete(tangentStiffnessMatrixOffset);
    tangentStiffnessMatrixOffset = new SparseMatrix(*tangentStiffnessMatrixOffset_);
  }
}

void IntegratorBaseSparse::AddTangentStiffnessMatrixOffset(SparseMatrix * tangentStiffnessMatrixOffset_)
{
  *tangentStiffnessMatrixOffset += *tangentStiffnessMatrixOffset_;
}

void IntegratorBaseSparse::ClearTangentStiffnessMatrixOffset()
{
  delete(tangentStiffnessMatrixOffset);
  tangentStiffnessMatrixOffset = NULL;
}


} // namespace vega
