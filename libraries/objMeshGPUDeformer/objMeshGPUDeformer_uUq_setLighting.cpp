/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "objMeshGPUDeformer" library , Copyright (C) 2007 CMU, 2009 MIT,      *
 *                                                        2018 USC       *
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

#include "objMeshGPUDeformer_uUq_setLighting.h"

namespace vega 
{

void ObjMeshGPUDeformer_uUq_setLighting::SetLighting(
  ObjMeshGPUDeformer_uUq * renderGPUObject, Lighting * lighting)
{
  float ambientIntensity = lighting->GetAmbientIntensity();
  renderGPUObject->SetAmbientIntensity(ambientIntensity);

  float lightPos[16];
  float lightIntensity[4];

  int numLights = 0;

  for(int i=0; i<8; i++)
  {
    if (!lighting->IsLightEnabled(i))
      continue;

    lighting->GetLightPosition(i, &lightPos[4*numLights]);
    lightIntensity[numLights] = lighting->GetLightIntensity(i);

    numLights++;

    if (numLights == 4) // our fragment shader supports 4 lights max
      break;
  }

  int lightID=0;
  for(lightID=0; lightID<numLights; lightID++)
  {
    renderGPUObject->SetLightPosition(lightID, &lightPos[4*lightID]);
    renderGPUObject->SetLightIntensity(lightID, lightIntensity[lightID]);
  }
  renderGPUObject->EnableAmbientLight(lighting->IsAmbientEnabled());
  renderGPUObject->EnableDiffuseLight(lighting->IsDiffuseEnabled());
  renderGPUObject->EnableSpecularLight(lighting->IsSpecularEnabled());

/*
  // these lights were set to their default values already in the constructor of the uUq_buffer or uUq_fbo class
  float zero[4] = {0,0,0,0};
  for(; lightID<4; lightID++)
  {
    renderGPUObject->SetLightPosition(lightID, zero);
    renderGPUObject->SetLightIntensity(lightID, 0);
  }
  */
}


} // namespace vega
