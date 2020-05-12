#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
 
const int
	MAXN = 1000000,
	MAXLGN = 20;
 
int N, Q;
int pos[MAXN];
int arr[MAXN];
int zip[MAXN];
int tree[MAXN];

struct PSeg {
  struct node {
    int val, L, R, size;
  } buff[2*MAXN*MAXLGN];
  int cant;
  int build( int lo, int hi ) {
    if ( lo > hi ) return 0;
  
    int idx = ++cant;
    
    int mid = ( lo + hi ) / 2;
    buff[idx] = (node){ mid, build( lo, mid - 1 ), build( mid + 1, hi ), 0 };
    return idx;
  }
  
  int update( int x, int val, int amount ) {
  
    if ( x == 0 ) return 0;
  
    int idx = ++cant;
    
    int L = buff[x].L;
    int R = buff[x].R;
    if ( val < buff[x].val ) L = update( L, val, amount );
    if ( val > buff[x].val ) R = update( R, val, amount );
    
    buff[idx] = (node){ buff[x].val, L, R, buff[x].size + amount };
  
    return idx;
  }
  
  int query( int x, int val ) {
    if ( val < buff[x].val )
      return query( buff[x].L, val ) + buff[x].size -	buff[ buff[x].L ].size;
  
    if ( val > buff[x].val )
      return query( buff[x].R, val );
  
    return buff[x].size - buff[ buff[x].L ].size;
  }
} seg;
 
int main() {
 
	scanf( "%d", &N );
  for (int i = 0; i < N; i++) scanf("%d", &arr[i]);
  for (int i = 0; i < N; i++) zip[i] = arr[i];
  sort(zip, zip+N);
  auto zu = unique(zip, zip+N);
  for (int i = 0; i < N; i++) arr[i] = lower_bound(zip, zu, arr[i]) - zip;
 
	tree[0] = seg.build( 1, N );
	for ( int i = 1; i <= N; i++ ) {
		int x, posx;
    x = arr[i-1];
		posx = pos[x];
		if ( posx != 0 )
			tree[i] = seg.update( seg.update( tree[i - 1], posx, -1 ), i, +1 );
		else
			tree[i] = seg.update( tree[i - 1], i, +1 );
		pos[x] = i;
	}
 
  int ans = 0;
	scanf( "%d", &Q );
	while ( Q-- ) {
		int lo, hi;
		scanf( "%d %d", &lo, &hi );
    lo += ans;
    ans = seg.query( tree[hi], lo );
		printf( "%d\n", seg.query( tree[hi], lo ) );
	}
 
	return 0;
}