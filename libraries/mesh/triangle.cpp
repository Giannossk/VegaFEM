/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "mesh" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC           *
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Jernej Barbic, Christopher Twigg, Daniel Schroeder      *
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
  A triangle
  Jernej Barbic, CMU
*/

#if defined(_WIN32) || defined(WIN32)
  #pragma warning(disable : 4996)
  #pragma warning(disable : 4267)
  #pragma warning(disable : 4244)
#endif

#include "openGL-headers.h"

#include <set>
#include <algorithm>
#include "triangle.h"
#include "tribox3.h"

using namespace std;

namespace vega 
{

bool TriangleBasic::doesIntersectBox(const BoundingBox & bbox) const
{
  // prepare the data and call the "triBoxOverlap" worker routine
  const Vec3d & center = bbox.center();
  const Vec3d & halfSides = bbox.halfSides();
  return triBoxOverlap(&center[0], &halfSides[0], &vertex[0][0], &vertex[1][0], &vertex[2][0]);
}

int TriangleBasic::pointSide(const Vec3d & point) const
{
  Vec3d normal = cross(vertex[1] - vertex[0], vertex[2] - vertex[0]);
  double dir = dot(point - vertex[0], normal);
  return (dir > 0 ? 1 : (dir < 0 ? -1 : 0));
}

int TriangleBasic::lineSegmentIntersection(const Vec3d & segmentStart, const Vec3d & segmentEnd, Vec3d * intersectionPoint, double * intersectionParameter, double barycentricWeight[3]) const
{
  // Jernej Barbic, CMU, 2005
  // code modified from the following code:

  // ------------------------------------
  // Copyright 2001, softSurfer (www.softsurfer.com)
  // This code may be freely used and modified for any purpose
  // providing that this copyright notice is included with it.
  // SoftSurfer makes no warranty for this code, and cannot be held
  // liable for any real or imagined damage resulting from its use.
  // Users of this code must verify correctness for their application.
  // ------------------------------------

  //    Output: intersection point (when it exists)
  //    Return: -1 = triangle is degenerate (a segment or point)
  //             0 = disjoint (no intersect)
  //             1 = intersect in unique point I1
  //             2 = are in the same plane

  Vec3d u, v, n;             // triangle vectors
  Vec3d dir, w0, w;          // ray vectors
  double r, a, b;             // params to calc ray-plane intersect

  // get triangle edge vectors and plane normal
  u = vertex[1] - vertex[0];
  v = vertex[2]- vertex[0];
  n = cross(u, v);             // cross product
  if ((n[0] == 0) &&         // triangle is degenerate
      (n[1] == 0) &&
      (n[2] == 0) )
    return -1;                 // do not deal with this case

  dir = segmentEnd - segmentStart;             // ray direction vector
  w0 = segmentStart - vertex[0];
  a = -dot(n,w0);
  b = dot(n,dir);
  if (b == 0)
  {
    // ray is parallel to triangle plane
    if (a == 0)                // ray lies in triangle plane
      return 2;
    else
      return 0;             // ray disjoint from plane
  }

  // get intersection point of ray with triangle plane
  r = a / b;
  if (r < 0.0)                   // ray goes away from triangle
    return 0;                  // => no intersect
  // for a segment, also test if (r > 1.0) => no intersect
  if (r > 1.0)                   // ray goes away from triangle
    return 0;                  // => no intersect
  if(intersectionParameter)
    *intersectionParameter = r;

  if(intersectionPoint)
  {
    *intersectionPoint = segmentStart + r * dir;           // intersect point of ray and plane
    w = *intersectionPoint - vertex[0];
  }
  else
    w = segmentStart + r * dir - vertex[0];

  // is intersectionPoint inside T?
  double uu, uv, vv, wu, wv, D;
  uu = dot(u,u);
  uv = dot(u,v);
  vv = dot(v,v);

  wu = dot(w,u);
  wv = dot(w,v);
  D = uv * uv - uu * vv;

  // get and test parametric coords
  double s, t;
  s = (uv * wv - vv * wu) / D;
  if (s < 0.0 || s > 1.0)        // intersectionPoint is outside T
    return 0;
  t = (uv * wu - uu * wv) / D;
  if (t < 0.0 || (s + t) > 1.0)  // intersectionPoint is outside T
    return 0;

  if(barycentricWeight)
  {
    barycentricWeight[0] = 1 - s - t;
    barycentricWeight[1] = s;
    barycentricWeight[2] = t;
  }
  return 1;                      // intersectionPoint is in T
}

#ifdef ENABLE_OpenGL
void TriangleBasic::render() const
{
   Vec3d a = vertex[0];
   Vec3d b = vertex[1];
   Vec3d c = vertex[2];

   glBegin(GL_TRIANGLES);
     glVertex3f(a[0],a[1],a[2]);
     glVertex3f(b[0],b[1],b[2]);
     glVertex3f(c[0],c[1],c[2]);
   glEnd();
}

void TriangleBasic::renderEdges() const
{
   Vec3d a = vertex[0];
   Vec3d b = vertex[1];
   Vec3d c = vertex[2];

   glBegin(GL_LINES);
     glVertex3f(a[0],a[1],a[2]);
     glVertex3f(b[0],b[1],b[2]);
     glVertex3f(b[0],b[1],b[2]);
     glVertex3f(c[0],c[1],c[2]);
     glVertex3f(c[0],c[1],c[2]);
     glVertex3f(a[0],a[1],a[2]);
   glEnd();
}
#endif

template<class TriangleClass>
void makeUniqueList(const vector<TriangleClass*> & triangleList, vector<TriangleClass*> & uniqueList)
{
  uniqueList = triangleList;
  makeUniqueList(uniqueList);
}

template<class TriangleClass>
void makeUniqueList(vector<TriangleClass*> & triangleList)
{
  sort(triangleList.begin(), triangleList.end());
  auto newEnd = unique(triangleList.begin(), triangleList.end());
  triangleList.resize(distance(triangleList.begin(), newEnd));
}

void TriangleWithCollisionInfo::ComputeCollisionInfo()
{
  // first, determine the affine transformation that maps the triangle into xy plane,
  // with first vertex to the origin,
  // second vertex on the positive x-axis, and
  // with a positive second coordinate for the third vertex

  Vec3d p0Temp = vertex[0];
  Vec3d p1Temp = vertex[1];
  Vec3d p2Temp = vertex[2];

  double sideLengths[3] = { len(p1Temp-p0Temp), len(p2Temp-p1Temp), len(p0Temp-p2Temp) };

  int longestIndex = -1;
  double longestSide = -1.0;

  for(int i=0; i<3; i++)
  {
    if (sideLengths[i] >= longestSide)
    {
      longestSide = sideLengths[i];
      longestIndex = i;
    }
  }

  if (longestIndex < 0)
  {
    // this should never happen
    printf("Warning: an internal index is negative.\n");
    longestIndex = 0; // we could also exit here
  }

  Vec3d p0,p1,p2;

  if (longestIndex == 0)
  {
    p0 = p0Temp;
    p1 = p1Temp;
    p2 = p2Temp;

    permutation[0] = 0;
    permutation[1] = 1;
    permutation[2] = 2;
    permutation[3] = 3;
    permutation[4] = 4;
    permutation[5] = 5;
  }
  else
  if (longestIndex == 1)
  {
    p0 = p1Temp;
    p1 = p2Temp;
    p2 = p0Temp;

    permutation[0] = 1;
    permutation[1] = 2;
    permutation[2] = 0;
    permutation[3] = 4;
    permutation[4] = 5;
    permutation[5] = 3;
  }
  else // (longestIndex == 2)
  {
    p0 = p2Temp;
    p1 = p0Temp;
    p2 = p1Temp;

    permutation[0] = 2;
    permutation[1] = 0;
    permutation[2] = 1;
    permutation[3] = 5;
    permutation[4] = 3;
    permutation[5] = 4;
  }

  //  0: vertex0
  //  1: vertex1
  //  2: vertex2
  //  3: edge among 01
  //  4: edge among 12
  //  5: edge among 20
  //  6: the face itself

  // now, p0,p1,p2 have been renumbered and permutation has been set

  sidea = sideLengths[permutation[0]]; // p1-p0
  sideb = sideLengths[permutation[1]]; // p2-p1
  sidec = sideLengths[permutation[2]]; // p0-p2

  Vec3d q1T,q2T,q3T;

  q1T = (p1-p0)/sidea;

  q3T = norm(cross(p1-p0,p2-p0));

  q2T = cross(q3T,q1T);

  // assemble matrix Q
  Q = Mat3d(q1T, q2T, q3T); // three rows

  x0 = (-1)*Q*p0;

  // sanity checks
  Vec3d y;
  y = Q * p0 + x0;
  if (len(y) > 1E-5)
  {
    cout << "Warning: transformation does not map p0 vector to the origin." << endl;
  }
  if (sidea < 0)
  {
    cout << "Warning: distance parameter a=" << sidea << " is negative." << endl;
  }

  if (sidea == 0)
  {
    cout << "Warning: distance parameter a=" << sidea << " is zero. Degenerate triangle?" << endl;
  }

  y = Q * p1 + x0;
  if (len(y-Vec3d(sidea,0,0)) > 1E-5)
  {
    cout << "Warning: transformation does not map p1 vector to (a,0,0)." << endl;
  }
  y = Q * p2 + x0;
  if (fabs(y[2]) > 1E-5)
  {
    cout << "Warning: transformation does not map p2 vector into the xy plane (z=" << y[2] << ")." << endl;
  }
  if (y[1] < 0)
  {
    cout << "Warning: transformation does not map p2 vector into the upper half of the xy plane. (y=" << y[1] << ")." << endl;
  }
  if (y[0] < 0)
  {
    cout << "Warning: transformation does not map p2 vector into the positive right half of the xy plane. (x=" << y[0] << ")." << endl;
  }
  if (y[0] > sidea)
  {
    cout << "Warning: transformation does not map p2 vector into a vector with smaller x-coordinate than sidea=" << sidea <<
     " (x=" << y[0] << ")." << endl;
  }

  area = 0.5 * sidea * y[1];

  // cache normals for line distance tests
  // compute image of p2 in the xy plane
  Vec3d P2_3d = Q * p2 + x0;
  Vec2d P2(P2_3d[0],P2_3d[1]);
  Vec2d P1(sidea,0);
  Vec2d P0(0,0);

  Vec2d n1 = norm(P2-P1);
  // s1 equals n1 rotate 90 deg clockwise
  Vec2d s1 = Vec2d(n1[1],-n1[0]);
  S1 = Vec3d(s1[0],s1[1],-dot(P1,s1));
  N11 = Vec3d(n1[0],n1[1],-dot(P1,n1));
  N12 = Vec3d(n1[0],n1[1],-dot(P2,n1));

  Vec2d n2 = norm(P0-P2);
  // s2 equals n2 rotate 90 deg clockwise
  Vec2d s2 = Vec2d(n2[1],-n2[0]);
  S2 = Vec3d(s2[0],s2[1],-dot(P2,s2));
  N21 = Vec3d(n2[0],n2[1],-dot(P2,n2));
  N22 = Vec3d(n2[0],n2[1],-dot(P0,n2));
}

#undef __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
#include "triangle-closestPoint.cpp"
#define __VERSION_WITH_BARYCENTRIC_COORDS_JNB_CMU__
#include "triangle-closestPoint.cpp"

TriangleWithCollisionInfoAndPseudoNormals::TriangleWithCollisionInfoAndPseudoNormals
(const Vec3d & first_g, const Vec3d & second_g, const Vec3d & third_g, const Vec3d pseudoNormals[7]): TriangleWithCollisionInfo(first_g,second_g,third_g)
{
  ComputeCollisionInfo();
  pseudoNormal_[0] = pseudoNormals[0];
  pseudoNormal_[1] = pseudoNormals[1];
  pseudoNormal_[2] = pseudoNormals[2];
  pseudoNormal_[3] = pseudoNormals[3];
  pseudoNormal_[4] = pseudoNormals[4];
  pseudoNormal_[5] = pseudoNormals[5];
  pseudoNormal_[6] = pseudoNormals[6];

  pseudoClosestPosition_[0] = vertex[0];
  pseudoClosestPosition_[1] = vertex[1];
  pseudoClosestPosition_[2] = vertex[2];
  pseudoClosestPosition_[3] = 0.5 * (vertex[0] + vertex[1]);
  pseudoClosestPosition_[4] = 0.5 * (vertex[1] + vertex[2]);
  pseudoClosestPosition_[5] = 0.5 * (vertex[2] + vertex[0]);
  pseudoClosestPosition_[6] = 1.0 / 3 * (vertex[0] + vertex[1] + vertex[2]);
}

template void makeUniqueList<TriangleBasic>(const vector<TriangleBasic*> & triangleList, vector<TriangleBasic*> & uniqueList);
template void makeUniqueList<TriangleBasic>(vector<TriangleBasic*> & triangleList);

template void makeUniqueList<TriangleWithCollisionInfo>(const vector<TriangleWithCollisionInfo*> & triangleList, vector<TriangleWithCollisionInfo*> & uniqueList);
template void makeUniqueList<TriangleWithCollisionInfo>(vector<TriangleWithCollisionInfo*> & triangleList);

template void makeUniqueList<TriangleWithCollisionInfoAndPseudoNormals>(const vector<TriangleWithCollisionInfoAndPseudoNormals*> & triangleList, vector<TriangleWithCollisionInfoAndPseudoNormals*> & uniqueList);
template void makeUniqueList<TriangleWithCollisionInfoAndPseudoNormals>(vector<TriangleWithCollisionInfoAndPseudoNormals*> & triangleList);


} // namespace vega
