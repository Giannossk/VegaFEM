/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "basicAlgorithms" library , Copyright (C) 2007 CMU, 2009 MIT, 2018 USC*
 * All rights reserved.                                                  *
 *                                                                       *
 * Code authors: Yili Zhao, Jernej Barbic                                *
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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "disjointSet.h"

using namespace std;

namespace vega 
{

void DisjointSet::makeSet(void)
{
  for(size_t i = 0; i < parent.size(); i++)
  {
    parent[i] = NO_SUCCESSOR;  // each object is initially a root of a tree
    depth[i] = 0;
  }
}

void DisjointSet::extendSizeTo(int num)
{
  assert(num >= (int)parent.size());

  parent.resize(num, NO_SUCCESSOR);
  depth.resize(num, 0);
}

int DisjointSet::findSet(int x) const
{
  if (x < 0 || x >= (int)(parent.size()))
  {
    std::cout << "Error in DisjointSet::findSet(int x): the x value is illegal." << std::endl;
    exit(0);
  }
  int ancestor = x;
  while(parent[ancestor] >= 0)
    ancestor = parent[ancestor];  // backtrack the ancestor
  //path compression
  while(x != ancestor)
  {
    int temp = parent[x];
    parent[x] = ancestor;
    x = temp;
  }
  return ancestor;  // here ancestor should be >=0
}

void DisjointSet::unionSet(int x, int y)
{
  int size = parent.size();
  if (x < 0 || x >= size)
  {
    std::cout << "Error in DisjointSet::UnionSet(int x, int y): the x value is illegal." << std::endl;
    exit(0);
  }
  if (y < 0 || y >= size)
  {
    std::cout << "Error in DisjointSet::UnionSet(int x, int y): the y value is illegal." << std::endl;
    exit(0);
  }
  int ancestor1 = findSet(x);
  int ancestor2 = findSet(y);
  if (ancestor1 == ancestor2)
    return; // they are already in the same set

  if (depth[ancestor1] < depth[ancestor2]) // set 2 is deeper
  {
    parent[ancestor1] = ancestor2;
  }
  else  if (depth[ancestor1] > depth[ancestor2]) // set 1 is deeper
  {
    parent[ancestor2] = ancestor1;
  }
  else // set 1 and 2 have same depth
  {
    parent[ancestor2] = ancestor1;
    depth[ancestor1]++; // we have to increase the depth
  }
}

std::vector<int> DisjointSet::createOldToNewIDMapping()
{
  std::vector<int> old2new(size());
  int numNewIDs = 0;
  std::vector<int> setRepID2newID(size(), -1);
  for(int i = 0; i < size(); i++)
  {
    int repID = findSet(i); // first, store set representive IDs to old2new
    if (setRepID2newID[repID] < 0)
    {
      setRepID2newID[repID] = (numNewIDs++);
    }
    old2new[i] = setRepID2newID[repID];
  }
  return old2new;
}

////////////////////////////////////////////////////////////////
//               DisjointSetDynamic
////////////////////////////////////////////////////////////////

int DisjointSetDynamic::getSetID(int elementID)
{
  auto it = setID.find(elementID);
  if (it == setID.end())
  {
    int newSetID = set.size();
    setID.emplace(elementID, newSetID);
    set.extendSizeTo(newSetID + 1);
    return newSetID;
  }
  return it->second;
}

int DisjointSetDynamic::findSet(int elementID)
{
  auto it = setID.find(elementID);
  if (it == setID.end())
  {
    int newSetID = set.size();
    setID.emplace(elementID, newSetID);
    set.extendSizeTo(newSetID + 1);
    return newSetID;
  }
  else
  {
    return set.findSet(it->second);
  }
}

void DisjointSetDynamic::unionSet(int x, int y)
{
  int setIDx = getSetID(x);
  int setIDy = getSetID(y);
  set.unionSet(setIDx, setIDy);
}

std::vector<std::vector<int>> DisjointSetDynamic::getAllSets() const
{
  std::map<int, std::vector<int>> sets; // rep setID -> elementIDs
  for(const auto & p : setID)
  {
    int eleID = p.first;
    int setID = p.second;
    sets[set.findSet(setID)].push_back(eleID);
  }
  std::vector<std::vector<int>> ret;
  for(auto & p : sets)
  {
    ret.emplace_back(move(p.second));
  }

  return ret;
}

} // namespace vega
