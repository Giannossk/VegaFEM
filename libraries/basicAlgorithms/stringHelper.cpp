/*************************************************************************
 *                                                                       *
 * Vega FEM Simulation Library Version 4.0                               *
 *                                                                       *
 * "basicAlgorithms" library , Copyright (C) 2018 USC                    *
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

#include "stringHelper.h"
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

namespace vega 
{

bool endWith(const std::string & str, const std::string & substr)
{
  if (str.size() < substr.size())
    return false;
  return std::equal(str.begin() + (str.size() - substr.size()), str.end(), substr.begin());
}

bool iendWith(const std::string & str, const std::string & substr)
{
  if (str.size() < substr.size())
    return false;
  for(auto iter = str.begin() + (str.size() - substr.size()), iter2 = substr.begin(); iter != str.end(); iter++, iter2++)
  {
    if (toupper(*iter) != toupper(*iter2))
      return false;
  }
  return true;
}

bool iendWith(const std::string & str, const char * substr)
{
  size_t sublen = strlen(substr);
  if (str.size() < sublen)
    return false;
  for(auto iter = str.begin() + (str.size() - sublen); iter != str.end(); iter++, substr++)
  {
    if (toupper(*iter) != toupper(*substr))
      return false;
  }
  return true;
}

void stripSelf(std::string & s)
{
  if (s.size() == 0)
    return;
  size_t start = 0; // the index for the first non-space character in s
  for(; start < s.size() && isspace(s[start]); start++) ;
  if (start == s.size()) // the entire string contains only white-space character
  {
    s.clear();
    return;
  }
  size_t end = s.size() - 1;
  for(; isspace(s[end]); end--) ; // end will not be < start because there must be a non-space character in s
  // for(; end >= 0 && isspace(s[end]); end--) ;
  // assert(start <= end);
  s = s.substr(start, end - start + 1);
}

std::string strip(const std::string & s)
{
  if (s.size() == 0)
    return s;
  size_t start = 0; // the index for the first non-space character in s
  for(; start < s.size() && isspace(s[start]); start++) ;
  if (start == s.size()) // the entire string contains only white-space character
    return std::string();

  size_t end = s.size() - 1;
  for(; isspace(s[end]); end--) ; // end will not be < start because there must be a non-space character in s
  // for(; end >= 0 && isspace(s[end]); end--) ;
  // assert(start <= end);
  return s.substr(start, end - start + 1);
}

char * stripLight(char * s)
{
  size_t start = 0;
  for(; s[start] != '\0' && isspace(s[start]); start++) ;
  if (s[start] == '\0')  // empty string
    return s+start;

  size_t end = strlen(s) - 1;
  for(; isspace(s[end]); end--) ;
  s[end+1] = '\0';
  return s+start;
}

// convert string to uppercase
void upperCase(char * s)
{
  for(size_t i = 0, num = strlen(s); i < num; i++)
    s[i] = toupper(s[i]);
}

void upperCase(std::string & s)
{
  for(size_t i = 0, num = s.size(); i < num; i++)
    s[i] = toupper(s[i]);
}

} // namespace vega
