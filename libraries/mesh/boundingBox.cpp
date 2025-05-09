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

//  Bounding Box
//  Author: Jernej Barbic, CMU

#include "openGL-headers.h"

#include <float.h>
#include <vector>
#include <iostream>
#include <cassert>

#include "boundingBox.h"
#include "triangle.h"
#include "valueIndex.h"

using namespace std;

namespace vega 
{

BoundingBox::BoundingBox(int numVertices, const Vec3d * vertices)
{
  bmin_ = Vec3d(+DBL_MAX, +DBL_MAX, +DBL_MAX);
  bmax_ = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  for(int i = 0; i < numVertices; i++)
  {
    updateOnePoint(vertices[i]);
  }
  updateData();
}

BoundingBox::BoundingBox(const vector<BoundingBox> & bbs)
{
  // set bmin_, bmax_
  bmin_ = Vec3d(+DBL_MAX, +DBL_MAX, +DBL_MAX);
  bmax_ = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  for(size_t i = 0; i < bbs.size(); i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if (bbs[i].bmin()[j] < bmin_[j])
        bmin_[j] = bbs[i].bmin()[j];
      if (bbs[i].bmax()[j] > bmax_[j])
        bmax_[j] = bbs[i].bmax()[j];
    }
  }
  updateData();
}


template<class Triangle>
void BoundingBox::buildFromTriangles(const vector<Triangle> & tripool)
{
  // set bmin_, bmax_
  bmin_ = Vec3d(+DBL_MAX, +DBL_MAX, +DBL_MAX);
  bmax_ = Vec3d(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  for(unsigned int i=0; i < tripool.size(); i++) // over all vertices
  {
    Vec3d p = tripool[i].first();
    updateOnePoint(p);
    p = tripool[i].second();
    updateOnePoint(p);
    p = tripool[i].third();
    updateOnePoint(p);
  }

  updateData();
}

BoundingBox::BoundingBox(const std::vector<TriangleBasic> & bbs)
{
  buildFromTriangles(bbs);
}

BoundingBox::BoundingBox(const std::vector<TriangleWithCollisionInfo> & bbs)
{
  buildFromTriangles(bbs);
}

BoundingBox::BoundingBox(const std::vector<TriangleWithCollisionInfoAndPseudoNormals> & bbs)
{
  buildFromTriangles(bbs);
}

void BoundingBox::regularize()
{
  Vec3d center_ = 0.5 * (bmin_ + bmax_);
  Vec3d halfside_ = 0.5* (bmax_ - bmin_);

  double maxHalf = halfside_[0];
  if (halfside_[1] > maxHalf)
    maxHalf = halfside_[1];
  if (halfside_[2] > maxHalf)
    maxHalf = halfside_[2];

  Vec3d cubeHalf_ = Vec3d(maxHalf,maxHalf,maxHalf);

  bmin_ = center_ - cubeHalf_;
  bmax_ = center_ + cubeHalf_;

  updateData();
}

void BoundingBox::updateOnePoint(const Vec3d & p)
{
  if (p[0] < bmin_[0])
    bmin_[0] = p[0];
  if (p[0] > bmax_[0])
    bmax_[0] = p[0];

  if (p[1] < bmin_[1])
    bmin_[1] = p[1];
  if (p[1] > bmax_[1])
    bmax_[1] = p[1];

  if (p[2] < bmin_[2])
    bmin_[2] = p[2];
  if (p[2] > bmax_[2])
    bmax_[2] = p[2];
}

void BoundingBox::updateData()
{
  center_ = 0.5 * (bmin_ + bmax_);
  halfSides_ = 0.5 * (bmax_ - bmin_);
}

bool BoundingBox::verifyBox() const
{
  if (!((bmin_[0] <= bmax_[0]) && (bmin_[1] <= bmax_[1]) && (bmin_[2] <= bmax_[2])))
  {
    printf("Error: inconsistent bounding box.\n");
    return false;
  }
  return true;
}

bool BoundingBox::checkInside(const Vec3d & p) const
{
  return bmin_[0] <= p[0] && p[0] <= bmax_[0] && bmin_[1] <= p[1] && p[1] <= bmax_[1] && bmin_[2] <= p[2] && p[2] <= bmax_[2];
}

bool BoundingBox::checkInside(const BoundingBox & b) const
{
  return bmin_[0] <= b.bmin_[0] && bmin_[1] <= b.bmin_[1] && bmin_[2] <= b.bmin_[2] &&
    bmax_[0] >= b.bmax_[0] && bmax_[1] >= b.bmax_[1] && bmax_[2] >= b.bmax_[2];
}

#ifdef ENABLE_OpenGL
void BoundingBox::render() const
{
  // render the bounding box
  Vec3d p0(bmin_[0],bmin_[1],bmin_[2]);
  Vec3d p1(bmax_[0],bmin_[1],bmin_[2]);
  Vec3d p2(bmax_[0],bmax_[1],bmin_[2]);
  Vec3d p3(bmin_[0],bmax_[1],bmin_[2]);

  Vec3d p4(bmin_[0],bmin_[1],bmax_[2]);
  Vec3d p5(bmax_[0],bmin_[1],bmax_[2]);
  Vec3d p6(bmax_[0],bmax_[1],bmax_[2]);
  Vec3d p7(bmin_[0],bmax_[1],bmax_[2]);

  #define VTX(i) (i)[0],(i)[1],(i)[2]
  glBegin(GL_LINES);
    glVertex3f(VTX(p0));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p0));

    glVertex3f(VTX(p0));
    glVertex3f(VTX(p4));
    glVertex3f(VTX(p1));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p2));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p3));
    glVertex3f(VTX(p7));

    glVertex3f(VTX(p4));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p5));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p6));
    glVertex3f(VTX(p7));
    glVertex3f(VTX(p7));
    glVertex3f(VTX(p4));
  glEnd();

  #undef VTX
}
#endif

// should this be turned into a self-modifying function?
void BoundingBox::expand(double expansionFactor)
{
  bmin_ = center_ - expansionFactor * halfSides_;
  bmax_ = center_ + expansionFactor * halfSides_;

  updateData();
}

void BoundingBox::expand(const Vec3d & p)
{
  updateOnePoint(p);
  updateData();
}

bool BoundingBox::lineSegmentIntersection(const Vec3d & segmentStart, const Vec3d & segmentEnd, Vec3d * intersection) const
{
  /*
    Jernej Barbic, CMU, 2005
    adapted from:

    Fast Ray-Box Intersection
    by Andrew Woo
    from "Graphics Gems", Academic Press, 1990
 */

  #define NUMDIM  3
  #define RIGHT   0
  #define LEFT    1
  #define MIDDLE  2

  Vec3d dir = segmentEnd - segmentStart;
  bool inside = true;
  char quadrant[NUMDIM];
  register int i;
  int whichPlane;
  double maxT[NUMDIM];
  double candidatePlane[NUMDIM];

  /* Find candidate planes; this loop can be avoided if
  rays cast all from the eye(assume perpsective view) */
  for (i=0; i<NUMDIM; i++)
    if(segmentStart[i] < bmin_[i])
    {
      quadrant[i] = LEFT;
      candidatePlane[i] = bmin_[i];
      inside = false;
    }
    else if (segmentStart[i] > bmax_[i])
    {
      quadrant[i] = RIGHT;
      candidatePlane[i] = bmax_[i];
      inside = false;
    }
    else
    {
      quadrant[i] = MIDDLE;
    }

  /* Ray origin inside bounding box */
  if(inside)
  {
    *intersection = segmentStart;
    return (true);
  }

  /* Calculate T distances to candidate planes */
  for (i = 0; i < NUMDIM; i++)
    if (quadrant[i] != MIDDLE && dir[i] !=0.)
      maxT[i] = (candidatePlane[i]-segmentStart[i]) / dir[i];
    else
      maxT[i] = -1.;

  /* Get largest of the maxT's for final choice of intersection */
  whichPlane = 0;
  for (i = 1; i < NUMDIM; i++)
    if (maxT[whichPlane] < maxT[i])
      whichPlane = i;

  /* Check final candidate actually inside box */
  if (maxT[whichPlane] < 0.0)
    return (false);
  if (maxT[whichPlane] > 1.0)
    return (false); // remove this for ray

  for (i = 0; i < NUMDIM; i++)
  {
    if (whichPlane != i)
    {
      (*intersection)[i] = segmentStart[i] + maxT[whichPlane] *dir[i];
      if ((*intersection)[i] < bmin_[i] || (*intersection)[i] > bmax_[i])
        return (false);
    }
    else
    {
      (*intersection)[i] = candidatePlane[i];
    }
  }

  return (true);                          /* ray hits box */

  #undef NUMDIM
  #undef RIGHT
  #undef LEFT
  #undef MIDDLE
}

bool BoundingBox::intersect(const BoundingBox & bb) const
{
  return
    (bmin_[0] <= bb.bmax_[0]) && (bmax_[0] >= bb.bmin_[0]) &&
    (bmin_[1] <= bb.bmax_[1]) && (bmax_[1] >= bb.bmin_[1]) &&
    (bmin_[2] <= bb.bmax_[2]) && (bmax_[2] >= bb.bmin_[2]);
}

double BoundingBox::distanceToPoint2(const Vec3d & point) const
{
  double distance = 0.0;
  for(int dim=0; dim<3; dim++)
  {
    if (point[dim] < bmin_[dim])
      distance += (bmin_[dim] - point[dim]) * (bmin_[dim] - point[dim]);
    else if (point[dim] > bmax_[dim])
      distance += (point[dim] - bmax_[dim]) * (point[dim] - bmax_[dim]);
  }
  return distance;
}

double BoundingBox::furthestDistanceToPoint2(const Vec3d & point) const
{
  double d2 = 0.0;
  for(int i=0; i<3; i++)
  {
    double dist;
    if (point[i] < center_[i])
      dist = bmax_[i] - point[i];
    else
      dist = point[i] - bmin_[i];
    d2 += dist * dist;
  }

  return d2;
}

std::pair<int, double> BoundingBox::longestSide() const
{
  MaxValueIndex vi;
  for(int i = 0; i < 3; i++)
    vi.update(bmax_[i] - bmin_[i], i);
  return make_pair(vi.index, vi.value);
}

void BoundingBox::print() const
{
  cout << (*this) << endl;
}


void BoundingBox::createChildBoundingBoxes(BoundingBox childCubeBoxes[8]) const
{
  const auto & center = center_;
  const auto & bmin = bmin_;
  const auto & bmax = bmax_;

  //         ^y (top)   (z: far)
  //         |
  //         |
  //(left)-------->x (right)
  //        /
  //       /
  //      z      (y:bottom)
  //     (z:near, z protruding the screen)
  // left bottom far
  childCubeBoxes[0].setbminmax(Vec3d(bmin[0], bmin[1], bmin[2]), Vec3d(center[0], center[1], center[2]));

  // right bottom far
  childCubeBoxes[1].setbminmax(Vec3d(center[0], bmin[1], bmin[2]), Vec3d(bmax[0], center[1], center[2]));

  // left top far
  childCubeBoxes[2].setbminmax(Vec3d(bmin[0], center[1], bmin[2]), Vec3d(center[0], bmax[1], center[2]));

  // right top far
  childCubeBoxes[3].setbminmax(Vec3d(center[0], center[1], bmin[2]), Vec3d(bmax[0], bmax[1], center[2]));

  // left bottom near
  childCubeBoxes[4].setbminmax(Vec3d(bmin[0], bmin[1], center[2]), Vec3d(center[0], center[1], bmax[2]));

  // right bottom near
  childCubeBoxes[5].setbminmax(Vec3d(center[0], bmin[1], center[2]), Vec3d(bmax[0], center[1], bmax[2]));

  // left top near
  childCubeBoxes[6].setbminmax(Vec3d(bmin[0], center[1], center[2]), Vec3d(center[0], bmax[1], bmax[2]));

  // right top near
  childCubeBoxes[7].setbminmax(Vec3d(center[0], center[1], center[2]), Vec3d(bmax[0], bmax[1], bmax[2]));
}

BoundingBox BoundingBox::getIntersection(const BoundingBox & bb) const
{
  Vec3d newBmin = bmin_, newBmax = bmax_;
  for(int i = 0; i < 3; i++)
  {
    if (bmin_[i] < bb.bmin_[i]) newBmin[i] = bb.bmin_[i];
    if (bmax_[i] > bb.bmax_[i]) newBmax[i] = bb.bmax_[i];
  }
  return BoundingBox(newBmin, newBmax);
}

template void BoundingBox::buildFromTriangles(const vector<TriangleBasic> & tripool);
template void BoundingBox::buildFromTriangles(const vector<TriangleWithCollisionInfo> & tripool);
template void BoundingBox::buildFromTriangles(const vector<TriangleWithCollisionInfoAndPseudoNormals> & tripool);



} // namespace vega
