/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "elasticForceModel" library , Copyright (C) 2007 CMU, 2009 MIT,       *
 *                                                       2018 USC        *
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

/*
  Nonlinear reduced StVK force model
  (via cubic polynomials)
*/

#ifndef _REDUCEDSTVKFORCE_MODEL_H_
#define _REDUCEDSTVKFORCE_MODEL_H_

#include <stdlib.h>
#include "StVKReducedInternalForces.h"
#include "StVKReducedStiffnessMatrix.h"
#include "reducedForceModel.h"

namespace vega 
{

class ReducedStVKForceModel : public virtual ReducedForceModel
{
public:
  
  // if you pass NULL for the stiffness matrix, the class will internally 
  // build it from the cubic polynomial; this is the most convenient option
  // (ability to pass stVKStiffnessMatrix was provided to save some 
  //  precomputation time; however, generating the matrix from the cubic 
  //  polynomial is actually very fast, so the speed-up is marginal)
  ReducedStVKForceModel(StVKReducedInternalForces * stVKReducedInternalForces, 
                    StVKReducedStiffnessMatrix * stVKStiffnessMatrix = NULL);
  virtual ~ReducedStVKForceModel();
  virtual void GetInternalForce(double * q, double * internalForces); 
  virtual void GetTangentStiffnessMatrix(double * q, double * tangentStiffnessMatrix);

  virtual void * GetReducedInternalForceClass() { return (void*)stVKReducedInternalForces; }
  virtual void * GetReducedStiffnessMatrixClass() { return (void*)stVKStiffnessMatrix; }

  // set a scaling factor for forces and stiffness matrix
  void SetScale(double scale_) { scale = scale_; }
  void UseScale(int useScale_) { useScale = useScale_; } // default: do not use scale

protected:
  StVKReducedInternalForces * stVKReducedInternalForces;
  StVKReducedStiffnessMatrix * stVKStiffnessMatrix;

  int useScale;
  double scale;

  bool own_stVKStiffnessMatrix;
};

} // namespace vega

#endif

