/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "hashTable" library , Copyright (C) 2007 CMU                          *
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

#include "hashTable.h"
#include <stdio.h>
#include <math.h>
#include <set>

using namespace std;

namespace vega 
{

template<class Data>
HashTable<Data>::HashTable(unsigned int suggestedSize)
{
  do
  {
    p = suggestedSize;
    suggestedSize++;
  }
  while (!isPrime(p));
  // here could also check that p is not close to a power of 2

  list<listEntry> emptyList;
  for(unsigned int i=0; i<p; i++)
    buckets.push_back(emptyList);
}

template<class Data>
bool HashTable<Data>::isPrime(unsigned int n)
{
  if (n <= 1)
    return false; 

  for(unsigned int i=2; i <= (unsigned int)(sqrt(1.0 * (n+1))); i++)
  {
    if (n % i == 0)
      return false;
  }

  return true;
}

template<class Data>
void HashTable<Data>::clear()
{
  for(unsigned int i=0; i<buckets.size(); i++)
    buckets[i].clear();
}

template<class Data>
void HashTable<Data>::insert(unsigned int key, Data & data)
{
  unsigned int hash = hashFunction(key);
  buckets[hash].push_back(make_pair(key,data));
}

template<class Data>
void HashTable<Data>::erase(unsigned int key)
{
  unsigned int hash = hashFunction(key);

  listIterator iter;
  for(iter = buckets[hash].begin(); iter != buckets[hash].end(); iter++)
  {
    if (iter->first == key)
    {
      buckets[hash].erase(iter);
      break;
    }
  } 
}

template<class Data>
Data * HashTable<Data>::find(unsigned int key)
{
  unsigned int hash = hashFunction(key);

  listIterator iter;
  for(iter = buckets[hash].begin(); iter != buckets[hash].end(); iter++)
  {
    if (iter->first == key)
    {
      return &(iter->second);
    }
  } 

  return NULL;
}

template<class Data>
bool HashTable<Data>::contains(unsigned int key, Data & data)
{
  unsigned int hash = hashFunction(key);

  listIterator iter;
  for(iter = buckets[hash].begin(); iter != buckets[hash].end(); iter++)
  {
    if ((iter->first == key) && (iter->second  == data))
    {
      return true;
    }
  } 

  return false;
}

template<class Data>
void HashTable<Data>::printInfo()
{
  double avgSize = 0;
  unsigned int maxSize = 0;
  int numEntries[6] = {0,0,0,0,0,0};

  for(unsigned int bucket=0; bucket < buckets.size(); bucket++)
  {
    unsigned int size = buckets[bucket].size();
    avgSize += size;
    if (size > maxSize)
      maxSize = size;

    int index = (size <=4 ? size : 5);
    numEntries[index]++;
  }
  avgSize *= (1.0 / buckets.size());

/*
  printf("===Hash table info===\n");
  printf("Num buckets: %d\n", (int)buckets.size());
  printf("Avg. bucket size: %G\n", avgSize);
  printf("Max bucket size: %d\n", maxSize);
  for(int i=0; i<6; i++)
    printf("%s%d: %d (%G%%)\n", (i<=4 ? "  " : ">="), i,
      numEntries[i], 100.0 * numEntries[i] / buckets.size());
  printf("=====================\n");
*/
}

// set<unsigned int>
template class HashTable<set<unsigned int>>;
template class HashTable<set<int>>;
template class HashTable<unsigned int>;
template class HashTable<int>;

} // namespace vega
