#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITE 0x7FFFFFFF

class Bipartite
{
public :
	vector<int> x_y;
	vector<int> y_x;
	vector< vector<int> > adj;
	vector<int> visited;
	int size;
	Bipartite(vector< vector<int> > &mat)
	{
		size = mat.size();
		x_y.resize(size, -1);
		y_x.resize(size, -1);
		visited.resize(size);
		adj.resize(size);
		for(int i=0;i<size;++i) {
			adj[i].reserve(size);
			for(int j=0;j<size;++j) {
				if(mat[i][j] == 0) {
					adj[i].push_back(j);
				}
			}
		}
	}
	bool maxMatch_DFS(int pos)
	{
		visited[pos] = 1;
		for(vector<int>::iterator it = adj[pos].begin(); it != adj[pos].end(); ++it) {
			int pre_owner = y_x[*it];
			if(pre_owner == -1 || (visited[pre_owner] == 0 && maxMatch_DFS(pre_owner))) {
				x_y[pos] = (*it);
				y_x[*it] = pos;
				return true;
			}
		}
		return false;
	}
	void maxMatch()
	{
		for(int i=0;i<size;++i) {
			fill(visited.begin(), visited.end(), 0);
			maxMatch_DFS(i);
		}
	}
};

void hungarian(vector< vector<int> > &mat, vector<int> &match)
{
	int size = mat.size();
	for(int i=0;i<size;++i) { // row minimum subtract
		int min = INFINITE;
		for(int j=0;j<size;++j) {
			if(mat[i][j] < min) {
				min = mat[i][j];
			}
		}
		for(int j=0;j<size;++j) {
			mat[i][j] -= min;
		}
	}
	for(int i=0;i<size;++i) { // col minimum subtract
		int min = INFINITE;
		for(int j=0;j<size;++j) {
			if(mat[j][i] < min) {
				min = mat[j][i];
			}
		}
		for(int j=0;j<size;++j) {
			mat[j][i] -= min;
		}
	}
	vector<int> xcover(size, 0);
	vector<int> ycover(size, 0);
	while(true) {
		int cover_cnt = 0;
		fill(xcover.begin(), xcover.end(), 0);
		fill(ycover.begin(), ycover.end(), 0);
		for(int i=0;i<size;++i) {
			for(int j=0;j<size;++j) {
				if(mat[i][j] == 0 && xcover[i] == 0 && ycover[j] == 0) {
					int zero_cnt = 0;
					for(int k=0;k<size;++k) {
						if(mat[i][k] == 0) ++zero_cnt;
						if(mat[k][j] == 0) --zero_cnt;
					}
					if(zero_cnt > 0) xcover[i] = 1;
					else ycover[j] = 1;
					++cover_cnt;
				}
			}
		}
		if(cover_cnt >= size) break;
		int alpha = INFINITE;
		for(int i=0;i<size;++i) {
			if(xcover[i] == 1) continue;
			for(int j=0;j<size;++j) {
				if(ycover[j] == 1) continue;
				if(mat[i][j] < alpha) {
					alpha = mat[i][j];
				}
			}
		}
		for(int i=0;i<size;++i) {
			if(xcover[i] == 1) continue;
			for(int j=0;j<size;++j) {
				if(ycover[j] == 1) continue;
				mat[i][j] -= alpha;
			}
		}
		for(int i=0;i<size;++i) {
			if(xcover[i] == 0) continue;
			for(int j=0;j<size;++j) {
				if(ycover[j] == 0) continue;
				mat[i][j] += alpha;
			}
		}
	}
	Bipartite bipartite(mat);
	bipartite.maxMatch();
	match = bipartite.x_y;
}

int main(int argc, char** argv)
{
	ifstream ifs;
	ifs.open("input.txt");
	int size;
	ifs >> size;
	vector< vector<int> > mat(size, vector<int>(size));
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			ifs >> mat[i][j];
		}
	}
	cout << "MAT : " << endl;
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	vector< vector<int> > tmp = mat;
	vector<int> match;
	hungarian(tmp, match);
	int res = 0;
	cout << "MATCH : ";
	for(int i=0;i<size;++i) {
		cout << match[i] << " ";
		res += mat[i][match[i]];
	}
	cout << endl;
	cout << "RES : " << res << endl;
	return 0;
}