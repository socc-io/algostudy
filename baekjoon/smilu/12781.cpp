#include <iostream>
#include <stdio.h>
#include <string>
 
using namespace std;
 
int main() {
   int a, c, x3, x4, b, d, y3, y4;
   cin >> a >> b >> c >> d >> x3 >> y3 >> x4 >> y4;
   int k = (d - b)*a - (c - a)*b;
   int result1 = (d - b)*x3 - (c - a)*y3 - k;
   int result2 = (d - b)*x4 - (c - a)*y4 - k;
   if (result1*result2 <= 0) cout<<"1";
   else cout << "0";
   return 0;
}