/*
  This code is based on code from the Geometric Tools library,
  which is licensed under a boost license.
  Such usage is permitted by the boost license; for details,
  please see the boost license below.
*/

// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

/*************************************************************************
 *                                                                       *
 * We release our improvements to the wildMagic code under our standard  *
 * Vega FEM license, as follows:                                         *
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "improvements to the wildMagic library" , Copyright (C) 2018 USC      *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code author: Yijing Li                                                *
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

#include "tetKey.h"

namespace vega 
{

const int OTetKey::tetFaceIndex[4][3] =  { { 1, 2, 3 }, { 0, 3, 2 }, { 0, 1, 3 }, { 0, 2, 1 } };

const int OTetKey::tetEdgeIndex[6][2] =
{
 { 0, 1 }, { 1, 2 }, { 2, 0 },
 { 0, 3 }, { 1, 3 }, { 2, 3 } };


void OTetKey::permute(int v0, int v1, int v2, int v3, int & r0, int & r1, int & r2, int & r3)
{
  int minInd = 0;
  r0 = v0;
  if (v1 < r0)
  {
    r0 = v1;
    minInd = 1;
  }
  if (v2 < r0)
  {
    r0 = v2;
    minInd = 2;
  }
  if (v3 < r0)
  {
    r0 = v3;
    minInd = 3;
  }

  if (minInd == 0)
    OTriKey::permute(v1, v2, v3, r1, r2, r3);
  else if (minInd == 1)
    OTriKey::permute(v0, v3, v2, r1, r2, r3);
  else if (minInd == 2)
    OTriKey::permute(v0, v1, v3, r1, r2, r3);
  else  // minInd == 3
      OTriKey::permute(v0, v2, v1, r1, r2, r3);
}


} // namespace vega
