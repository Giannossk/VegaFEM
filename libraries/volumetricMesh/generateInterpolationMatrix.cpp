/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "volumetricMesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC *
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

#include "generateInterpolationMatrix.h"

namespace vega 
{

void GenerateInterpolationMatrix::generate(int numTargetLocations, int numElementVertices, const int * vertices, const double * weights, SparseMatrix ** A, int numSourceVertices)
{
  SparseMatrixOutline outline(3*numTargetLocations);

  for(int vtx=0; vtx<numTargetLocations; vtx++)
  {
    for(int i=0; i<numElementVertices; i++)
    {
      for(int j=0; j<3; j++)
        outline.AddEntry(3*vtx+j, 3*vertices[numElementVertices*vtx+i]+j, weights[numElementVertices*vtx+i]);
    }
  }

  int numColumns = outline.GetNumColumns();
  for(int i=numColumns; i<3*numSourceVertices; i++)
    outline.AddEntry(0, i, 0.0);
  
  *A = new SparseMatrix(&outline);
}


} // namespace vega
