#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(void)
{
  ll ax1,ay1,ax2,ay2;
  scanf("%lld%lld%lld%lld", &ax1,&ay2,&ax2,&ay1);
  ll bx1,by1,bx2,by2;
  scanf("%lld%lld%lld%lld", &bx1,&by2,&bx2,&by1);
  ll mx = max(ax1,bx1), Mx = min(ax2,bx2);
  ll my = max(ay1,by1), My = min(ay2,by2);
  ll dx = Mx-mx, dy = My - my;
  if (dx < 0 || dy < 0) puts("0");
  else printf("%lld\n", dx*dy);
}