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

/*
  A general deformable scene object, rendered on GPU via interpolation
  See also sceneObject.h . 
*/

#ifndef _SCENEOBJECTDEFORMABLEGPU_H_
#define _SCENEOBJECTDEFORMABLEGPU_H_

#define GL_GLEXT_PROTOTYPES 1

#include "lighting.h"
#include "sceneObjectDeformable.h"
#include "objMeshGPUDeformer_coarseToFine_fbo.h"

namespace vega 
{

class SceneObjectDeformableGPU : public virtual SceneObjectDeformable
{
public:
  SceneObjectDeformableGPU(const char * filenameOBJ);
  virtual ~SceneObjectDeformableGPU();

  void SetInterpolation(int numCoarseVertices, int numElementVertices, int * vertices, double * weights);

  void SetCoarseDeformations(double * u); 

  virtual void Render();
  virtual void RenderShadow(double ground[4], double light[4]);
  //virtual void RenderVertices();
  //virtual void RenderEdges();

  virtual void SetLighting(Lighting * lighting);

  virtual void Getu(double * u);

protected:
  ObjMeshGPUDeformer_coarseToFine_fbo * render_coarseToFine;
};

} // namespace vega

#endif

