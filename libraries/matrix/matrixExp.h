/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "matrix" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC         *
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
  Matrix wrappers to expokit routines.
  Note: although the wrappers are templated, only the value real=double works.
  This is because expokit supports double precision matrix exponentials 
  (DGPADM), but does not currently include a single-precision routine SGPADM.
  See also matrix.h and expokit_xgpadm.h.
*/

#ifndef _MATRIXEXP_H_
#define _MATRIXEXP_H_

namespace vega 
{

// computes exp(mtx*t)
template<class real>
int MatrixExp(int m, real * mtx, real t, real * output, int ideg=6);

// computes w = exp(mtx*t)*v
template<class real>
int MatrixExpv(int m, real * mtx, real t, real * v, real * w, int ideg=6);

} // namespace vega

#endif
