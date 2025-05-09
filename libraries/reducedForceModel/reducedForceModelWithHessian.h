/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "reducedForceModel" library , Copyright (C) 2007 CMU, 2009 MIT,       *
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
  Abstract class for a reduced deformable material model, where the Hessian is available.
  Serves as a connecting class between reduced integrators and classes to calculate reduced internal forces and tangent stiffness matrices.
*/

#ifndef _REDUCEDFORCEMODELWITHHESSIAN_H_
#define _REDUCEDFORCEMODELWITHHESSIAN_H_

#include "reducedForceModel.h"

namespace vega 
{

class ReducedForceModelWithHessian : public virtual ReducedForceModel
{
public:
  ReducedForceModelWithHessian();
  virtual ~ReducedForceModelWithHessian();

  virtual void GetTangentHessianTensor(double * u, double * tangentHessianTensor) {}; 
  virtual void GetStiffnessMatrixCorrection(double * u, double * du, double * dK); 

  void TestHessian(int numTests, double qAmplitude);

protected:
  double * hessianBuffer;

  static void ContractTensorWithVector(int r, double * Hq, double * q, double * A);
};

} // namespace vega

#endif

