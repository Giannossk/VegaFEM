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

#ifndef _SCENEOBJECTDEFORMABLEGPU6DOF_H_
#define _SCENEOBJECTDEFORMABLEGPU6DOF_H_

#include "sceneObjectDeformableGPU.h"
#include "sceneObjectDeformable6DOF.h"

namespace vega 
{

class SceneObjectDeformableGPU6DOF : public SceneObjectDeformableGPU, public SceneObjectDeformable6DOF
{
public:

  SceneObjectDeformableGPU6DOF(const char * filenameOBJ);
  virtual ~SceneObjectDeformableGPU6DOF();

  virtual void Render();
/*
  virtual void RenderVertices();
  virtual void RenderVertices_Selection();
  virtual void RenderEdges();
  virtual void RenderVertices(int numVertices, int * vertexList);
*/
  virtual void RenderShadow(double ground[4], double light[4]);

protected:
};

} // namespace vega

#endif

