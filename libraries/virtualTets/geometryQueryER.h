/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "virtualTets" library , Copyright (C) 2018 USC                        *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Yijing Li, Jernej Barbic                                *
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

#ifndef GEOMETRYQUERYER_H
#define GEOMETRYQUERYER_H

#include "vec3ER.h"

namespace vega 
{

/*
  Helper functions for exact geometry operations.
*/

// Also returns the closest feature to the query point:
//  0: vertex0
//  1: vertex1
//  2: vertex2
//  3: edge among 01
//  4: edge among 12
//  5: edge among 20
//  6: the face itself
ER squaredDistanceToTriangle(const Vec3ER & queryPoint, const Vec3ER & vertex0, const Vec3ER & vertex1, const Vec3ER & vertex2, int & feature);

Vec3ER getClosestPointToTriangleWithFeature(const Vec3ER & queryPoint, const Vec3ER & vertex0, const Vec3ER & vertex1, const Vec3ER & vertex2, int feature);

} // namespace vega

#endif

