#!/usr/bin/python
#
# @ email becxer87@gmail.com
# @ author becxer
#

import sys
template = '''
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cstdlib>    // for atoi
#include <sstream>    // for stringstream
#include <cmath>    // for sqrt
#include <cstring>    // for memset
using namespace std;

#define INF 2139999999

int main(void) {
    int tc;
	char str[100]; 
    cin >> tc; 
    while(tc--) {
		cin >> str;
		cout << str << endl;



    }   
    return 0;
}
'''

if len(sys.argv) <= 1:
	print ''
	print 'usage : genCpp.py "problem_title" TYPE (default : ARGV)'
	print ''
	print ''
	exit()

title = sys.argv[1]
if len(sys.argv) >= 3:
	template = template.replace("ARGV",sys.argv[2])
template = template.replace("#title",title)
f = open(title+".cpp","w")
f.write(template)
f.close()
f = open(title+".input","w")
f.write("3\nhello-algostudy!\nhello-socc!\nhello-world!")
f.close()
print title + '.cpp ' + title + '.input generated'
