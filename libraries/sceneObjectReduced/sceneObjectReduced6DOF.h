/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "sceneObject" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC    *
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

#ifndef _SCENEOBJECTREDUCED6DOF_H_
#define _SCENEOBJECTREDUCED6DOF_H_

#include "sceneObject6DOF.h"
#include "sceneObjectReduced.h"

namespace vega 
{

class SceneObjectReduced6DOF : public virtual SceneObjectReduced, public SceneObject6DOF
{
public:

  SceneObjectReduced6DOF(const char * filenameOBJ, ModalMatrix * modalMatrix); 
  SceneObjectReduced6DOF(ObjMesh * objMesh, ModalMatrix * modalMatrix, bool deepCopy = true); 
  virtual ~SceneObjectReduced6DOF();

  virtual void GetSingleVertexPosition(int vertex, double * x, double * y, double * z);
  virtual void GetSingleVertexVelocity(int vertex, double * objectVel, double * objectAngVel, double * velx, double * vely, double * velz);

  virtual void Render() = 0;
  virtual void RenderVertices() = 0;
  virtual void RenderVertices_Selection() = 0;
  virtual void RenderEdges() = 0;
  virtual void RenderVertices(int numVertices, int * vertexList) = 0;
  virtual void RenderShadow(double ground[4], double light[4]) = 0;

  virtual void Setqvel(double * qvel); // copies qvel into internal state

protected:
  double * qvel;
};

} // namespace vega

#endif

