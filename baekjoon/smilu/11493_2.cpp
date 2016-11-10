#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

#define INFINITE 0x7FFFFFFF

void printVec(vector<int> &vec)
{
	for(int i=0;i<vec.size();++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}
void printSet(set<int> &s)
{
	for(set<int>::iterator it = s.begin(); it != s.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

void printMat(vector< vector<int> > &mat)
{
	int size = mat.size();
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

bool dfs_find_augmenting(int pos, vector< vector<int> > &graph, vector<int> &augmenting)
{
	int size = graph.size();
	if(pos == size-1) {
		augmenting.push_back(pos);
		return true;
	}
	augmenting.push_back(pos);
	for(int i=0;i<size;++i) {
		if(graph[pos][i] == 0) continue;
		if(find(augmenting.begin(), augmenting.end(), i) == augmenting.end()) {
			if(dfs_find_augmenting(i, graph, augmenting)) {
				return true;
			}
		}
	}
	augmenting.pop_back();
	return false;
}

int makeMatching(vector<int> &matching, vector<int> &matching_re, vector< vector<int> > &equal)
{
	int size = matching.size();
	int graph_size = size*2 + 2;
	vector< vector<int> > graph(graph_size, vector<int>(graph_size, 0));
	for(int i=0;i<size;++i) {
		graph[0][1+i] = 1;
		graph[1+size+i][graph_size-1] = 1;
		for(int j=0;j<size;++j) {
			graph[1+i][1+size+j] = equal[i][j];
		}
	}
	for(int i=0;i<size;++i) {
		int r = matching[i];
		if(r != -1) {
			graph[0][1+i] = 0;
			graph[1+i][0] = 1;
			graph[1+i][1+size+r] = 0;
			graph[1+size+r][1+i] = 1;
			graph[1+size+r][graph_size-1] = 0;
			graph[graph_size-1][1+size+r] = 1;
		}
	}
	vector<int> augmenting;
	while(dfs_find_augmenting(0, graph, augmenting)) {
		int aug_size = augmenting.size();
		for(int i=1;i<aug_size;++i) {
			graph[augmenting[i-1]][augmenting[i]] = 0;
			graph[augmenting[i]][augmenting[i-1]] = 1;
		}
		augmenting.clear();
	}
	fill(matching_re.begin(), matching_re.end(), -1);
	fill(matching.begin(), matching.end(), -1);
	int match_cnt = 0;
	for(int i=0;i<size;++i) {
		if(graph[0][1+i] == 0) {
			for(int j=0;j<size;++j) {
				if(graph[1+size+j][1+i] == 1) {
					matching[i] = j;
					matching_re[j] = i;
					++match_cnt;
					break;
				}
			}
		}
	}
	return match_cnt;
}

void makeEqual(vector< vector<int> > &equal, vector<int> &xlabel, vector<int> &ylabel, vector< vector<int> > &mat)
{
	int size = equal.size();
	for(int i=0;i<size;++i) {
		int xlabel_val = xlabel[i];
		for(int j=0;j<size;++j) {
			int ylabel_val = ylabel[j];
			equal[i][j] = xlabel_val + ylabel_val == mat[i][j] ? 1 : 0;
		}
	}
}

void makeNl(set<int> &Nl, set<int> &S, vector< vector<int> > &equal)
{
	Nl.clear();
	for(set<int>::iterator it = S.begin(); it != S.end(); ++it) {
		vector<int> &sc = equal[*it];
		int idx = 0;
		for(vector<int>::iterator it2 = sc.begin(); it2 != sc.end(); ++it2) {
			if((*it2) == 1) {
				Nl.insert(idx);
			}
			++idx;
		}
	}
}

void updateLabel(set<int> &S, set<int> &T, vector<int> &xlabel, vector<int> &ylabel,
	vector< vector<int> > &mat)
{
	int size = xlabel.size();
	int alpha = INFINITE;
	for(set<int>::iterator S_it = S.begin(); S_it != S.end(); ++S_it)
	{
		int s = *S_it;
		for(int y=0;y<size;++y) {
			if(T.find(y) != T.end()) continue;
			int newval = xlabel[s] + ylabel[y] - mat[s][y];
			if(newval < alpha) {
				alpha = newval;
			}
		}
	}
	// cout << "alpha : " << alpha << endl;
	for(set<int>::iterator it = S.begin(); it != S.end(); ++it) {
		xlabel[*it] -= alpha;
	}
	for(set<int>::iterator it = T.begin(); it != T.end(); ++it) {
		ylabel[*it] += alpha;
	}
}

int hungarianAlgorithm(vector< vector<int> > &mat)
{
	int size = mat.size();
	vector<int> xlabel(size);
	vector<int> ylabel(size,0);
	vector<int> matching(size, -1);
	vector<int> matching_reverse(size, -1);
	vector< vector<int> > equal(size, vector<int>(size));
	int match_cnt;
	// set initial matching, label
	for(int i=0;i<size;++i) {
		vector<int>::iterator max_it = max_element(mat[i].begin(), mat[i].end());
		xlabel[i] = *max_it;
		for(int j=0;j<size;++j) {
			if(mat[i][j] == *max_it && matching_reverse[j] == -1) {
				matching[i] = j;
				matching_reverse[j] = i;
				break;
			}
		}
	}
	makeEqual(equal, xlabel, ylabel, mat);
	match_cnt = makeMatching(matching, matching_reverse, equal);
	//
	set<int> S;
	set<int> T;
	set<int> Nl;
	int u = find(matching.begin(), matching.end(), -1) - matching.begin();
	S.insert(u);
	while(match_cnt != size) {
		/*cout << "--------------------------" << endl;
		printVec(xlabel); printVec(ylabel); printVec(matching);
		printMat(equal);
		cout << "s : "; printSet(S);
		cout << "t : "; printSet(T);
		cout << "Nl: "; printSet(Nl);*/
		makeNl(Nl, S, equal);
		bool skip = false;
		while(T != Nl) {
			for(set<int>::iterator nl_it = Nl.begin(); nl_it != Nl.end(); ++nl_it) {
				if(T.find(*nl_it) == T.end()) {
					int y = *nl_it;
					int z = matching_reverse[y];
					if(z == -1) {
						match_cnt = makeMatching(matching, matching_reverse, equal);
						int u = find(matching.begin(), matching.end(), -1) - matching.begin();
						S.clear(); S.insert(u);
						T.clear();
						skip = true;
					}
					else {
						S.insert(z);
						T.insert(y);
						makeNl(Nl, S, equal);
					}
					break;
				}
			}
			if(skip) break;
		}
		if(skip) continue;
		updateLabel(S, T, xlabel, ylabel, mat);
		makeEqual(equal, xlabel, ylabel, mat);
	}
	int res = 0;
	for(int i=0;i<size;++i) {
		res += mat[i][matching[i]];
	}
	return res;
}

void makeCost(vector< vector<int> > &cost, vector<int> &color, vector<int> &token, vector< vector<int> > &net)
{
	vector<int> wb;
	vector<int> bw;
	wb.reserve(250); bw.reserve(250);
	int n = color.size();
	for(int i=0;i<n;++i) {
		if(color[i] == 0 && token[i] == 1) {
			wb.push_back(i);
		}
		if(color[i] == 1 && token[i] == 0) {
			bw.push_back(i);
		}
	}
	n = wb.size();
	cost.resize(n, vector<int>(n, 0));
	for(int i=0;i<n;++i) {
		int wb_val = wb[i];
		for(int j=0;j<n;++j) {
			int bw_val = bw[j];
			cost[i][j] = net[wb_val][bw_val];
		}
	}
}

void FloydWarshall(vector< vector<int> > &net)
{
	int size = net.size();
	for(int k=0;k<size;++k) {
		for(int i=0;i<size;++i) {
			for(int j=0;j<size;++j) {
				if(net[i][k] == INFINITE || net[k][j] == INFINITE) continue;
				int new_val = net[i][k] + net[k][j];
				if(new_val < net[i][j]) {
					net[i][j] = new_val;
				}
			}
		}
	}
}

int optimizeMat(vector< vector<int> > &mat)
{
	int size = mat.size();
	int res = 0;
	bool do_something = false;
	int min = mat[0][0];
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(mat[i][j] < min) {
				min = mat[i][j];
			}
		}
	}
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			mat[i][j] -= min;
		}
	}
	res += min * size;
	for(int i=0;i<size;++i) {
		int min = mat[i][0];
		for(int j=1;j<size;++j) {
			if(mat[i][j] < min) {
				min = mat[i][j];
			}
		}
		if(min != 0) {
			for(int j=0;j<size;++j) {
				mat[i][j] -= min;
			}
			do_something = true;
			res += min;
		}
	}
	for(int i=0;i<size;++i) {
		int min = mat[0][i];
		for(int j=1;j<size;++j) {
			if(mat[j][i] < min) {
				min = mat[j][i];
			}
		}
		if(min != 0) {
			for(int j=0;j<size;++j) {
				mat[j][i] -= min;
			}
			do_something = true;
			res += min;
		}
	}
	return res;
}

void DO()
{
	// getInput
	int n, m;
	cin >> n >> m;
	vector< vector<int> > net(n, vector<int>(n, INFINITE));
	vector<int> color(n);
	vector<int> token(n);
	for(int i=0;i<m;++i) {
		int left, right;
		cin >> left >> right;
		--left; --right;
		net[left][right] = 1;
		net[right][left] = 1;
	}
	for(int i=0;i<n;++i) cin >> color[i];
	for(int i=0;i<n;++i) cin >> token[i];
	//////
	FloydWarshall(net);
	vector< vector<int> > cost;
	makeCost(cost, color, token, net);
	int opt = optimizeMat(cost);
	// cout << "COSTMAP : " << endl;
	// printMat(cost);
	int result = opt + hungarianAlgorithm(cost);
	// cout << "Result : " << result << endl;
	cout << result << endl;
}

void TEST()
{
	 vector< vector<int> > t(3, vector<int>(3));
	 t[0][0] = 1; t[0][1] = 2; t[0][2] = 3;
	 t[1][0] = 1; t[1][1] = 2; t[1][2] = 3;
	 t[2][0] = 1; t[2][1] = 2; t[2][2] = 3;
	 vector< vector<int> > e(2, vector<int>(2));
	 e[0][0] = 1; e[0][1] = 0;
	 e[1][0] = 0; e[1][1] = 1;
	 vector<int> matching(2, -1);
	 vector<int> matching_re(2, -1);
	 
	 cout << "Result : " << hungarianAlgorithm(t) << endl;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int idx = 0; idx < T; ++idx) {
		DO();
	}
	return 0;
}