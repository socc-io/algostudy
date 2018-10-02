//
//  KMP.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//

#pragma once

#include <vector>
#include <string>
using namespace std;
typedef vector<int> VI;

/*
Returns: 0-based index of the first match
Time: O(k) time
usage: KMP(string, key);
*/

void buildTable(string& w, VI& t)
{
  t = VI(w.length());  
  int i = 2, j = 0;
  t[0] = -1; t[1] = 0;
  
  while(i < w.length())
  {
    if(w[i-1] == w[j]) 
	{
		t[i] = j+1; 
		i++; 
		j++; 
	}
    else if(j > 0) 
    	j = t[j];
    else { t[i] = 0; i++; }
  }
}

int KMP(string& s, string& w)
{
  int m = 0, i = 0;
  VI t;
  
  buildTable(w, t);  
  while(m+i < s.length())
  {
    if(w[i] == s[m+i])
    {
      i++;
      if(i == w.length()) 
      	return m;
    }
    else
    {
      m += i-t[i];
      if(i > 0) 
      	i = t[i];
    }
  }  
  return s.length();
}