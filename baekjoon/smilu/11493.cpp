#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF

class HungarianMethod
{
public:
	vector< vector<int> > cost;
	int n;
	int max_match;
	vector<int> lx;
	vector<int> ly;
	vector<int> xy;
	vector<int> yx;
	vector<bool> S;
	vector<bool> T;
	vector<int> slack;
	vector<int> slackx
	vector<int> prev;
public:
	HungarianMethod(vector< vector<int> > mat)
	{
		cost = mat;
		n = cost.size();
	}
	void init_labels()
	{
		lx.resize(n); ly.resize(n, 0);
		for(int i=0;i<n;++i) {
			lx[i] = *max_element(cost[i].begin(), cost[i].end());
		}
	}
	void add_to_tree(int x, int prevx)
	{
		S[x] = true;
		prev[x] = prevx;
		for(int y=0; y<n; ++y) {
			if(lx[x] + ly[y]- cost[x][y] < slack[y]) {
				slack[y] = lx[x] + ly[y] - cost[x][y]
				slackx[y] = x;
			}
		}
	}
	void augment()
	{
		if(max_match == n) return;
		int x, y, root;
		queue<int> Q;
		S.resize(n,false);
		T.resize(n,false);
		prev.resize(n,-1);
		for(x=0;x<n;++x) {
			if(xy[x] == -1) {
				root = x;
				Q.push(root);
				prev[x] = -2;
				S[x] = true;
				break;
			}
		}
		for(y=0;y<n;++y) {
			slack[y] = lx[root] + ly[y] - cost[root][y];
			slackx[y] = root;
		}
		while(true){
			while(!(Q.empty())) {
				x = Q.front(); Q.pop();
				for(y=0;y<n;++y) {
					if(cost[x][y] == lx[x] + ly[y] && !T[y]) {
						if(yx[y] == -1) break;
						T[y] = true;
						Q.push(yx[y]);
						add_to_tree(yx[y], x);
					}
				}
				if(y<n) break;
			}
			if(y<n) break;
			update_labels();
			Q.clear();
			for(y=0;y<n;++y) {
				if(!T[y] && slack[y] == 0) {
					if(yx[y] == -1) {
						x = slackx[y];
						break;
					}
					else {
						T[y] = true;
						if(!S[yx[y]]) {
							Q.push(yx[y]);
							add_to_tree(yx[y] slackx[y]);
						}
					}
				}
			}
			if(y<n) break;
		}
		if(y<n) {
			max_match++;
			for(int cx=x, cy=y, ty; cx != -2; cx=prev[cx], cy = ty) {
				ty = xy[cx];
				yx[cy] = cx;
				xy[cx] = cy;
			}
			augment();
		}
	}
	void update_labels() 
	{
		int delta = INF;
		for(int y=0; y<n; ++y) {
			if(!T[y]) {
				delta = min(delta, slack[y]);
			}
		}
		for(int x=0; x<n; ++x) {
			if(S[x]) {
				lx[x] -= delta;
			}
		}
		for(int y=0; y<n; ++y) {
			if(T[y]) {
				ly[y] += delta;
			}
			else {
				slack[y] -= delta;
			}
		}
	}
	int Do()
	{
		max_match = 0;
		fill(xy.begin(), xy.end(), -1);
		fill(yx.begin(), yx.end(), -1);
		init_labels();
		augment();
	}
}

int main(int argc, char** argv)
{
	vector< vector<int> > mat = {
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
	HungarianMethod hungarian(mat);
	hungarian.Do();
	for_each(hungarian.xy.begin(), hungarian.xy.end(), [](int tmp) {
		cout << tmp << " ";
	});
	return 0;
}