#include <iostream>
#include <vector>

using namespace std;

#define INFINITE 214748364

int n, m;
int net[500][500];
int color[500];
int token[500];
int cost[250][250];
int size; // cost width, height
int matching[250];
int matching_reverse[250];
int xlabel[250];
int ylabel[250];
int graph[502][502];
int graph_size;
int S_array[250];
int S_idx;
int T_array[250];
int T_idx;
int S_check[250];
int T_check[250];
int Nl_array[250];
int Nl_check[250];
int Nl_idx;

int augment_path[500];
int augment_path_in[500];
int augment_path_idx;

int pickY()
{
	for(int i=0;i<Nl_idx;++i) {
		int nlval = Nl_array[i];
		if(T_check[nlval] == 0) {
			return nlval;
		}
	}
	return -1;
}

int NlEqualToT()
{
	for(int i=0;i<size;++i){
		if(Nl_check[i] != T_check[i]) {
			return false;
		}
	}
	return true;
}

void updateNl()
{
	Nl_idx++;
	for(int i=0;i<size;++i) Nl_check[i] = 0;
	for(int i=0;i<S_idx;++i) {
		int sidx = S_array[i];
		for(int j=0;j<size;++j) {
			if(Nl_check[j] == 1) continue;
			if(xlabel[sidx] + ylabel[j] == cost[sidx][j]) {
				Nl_array[Nl_idx++] = j;
				Nl_check[j] = 1;
			}
		}
	}
}

void updateLabel()
{
	int min = INFINITE;
	for(int i=0;i<size;++i) {
		if(S_check[i] == 0) continue;
		for(int j=0;j<size;++j) {
			if(T_check[j] == 1) continue;
			int newval = xlabel[i] + ylabel[j] - cost[i][j];
			if(newval < min) {
				min = newval;
			}
		}
	}
	for(int i=0;i<S_idx;++i) {
		xlabel[S_array[i]] -= min;
	}
	for(int i=0;i<T_idx;++i) {
		ylabel[T_array[i]] += min;
	}
}

int STInitialize()
{
	S_idx = 0; T_idx = 0;
	for(int i=0;i<size;++i) {
		S_check[i] = 0; T_check[i] = 0;
	}
	for(int i=0;i<size;++i) {
		if(matching[i] == -1) {
			S_array[S_idx++] = i;
			S_check[i] = 1;
			return i;
		}
	}
	return -1;
}

int perfect_matching()
{
	for(int i=0;i<size;++i) { // check all vertices matched
		if(matching[i] == -1) {
			return false;
		}
	}
	for(int i=0;i<size;++i) {
		for(int j=i+1;j<size;++j) {
			if(matching[i] == matching[j]) {
				return false;
			}
		}
	}
	return true;
}
int dfs_augment(int pos)
{
	if(pos == graph_size-1) {
		augment_path[augment_path_idx++] = pos;
		return 1;
	}
	augment_path[augment_path_idx++] = pos; // push
	augment_path_in[pos] = 1;
	for(int i=0;i<graph_size;++i) {
		if(augment_path_in[i] == 1) continue; // ignore what already pushed
		if(graph[pos][i] == 1) {
			if(dfs_augment(i)) {
				return 1;
			}
		}
	}
	augment_path_idx--; // pop
	augment_path_in[pos] = 0;
	return 0;
}

int find_augment(int pos)
{
	augment_path_idx = 0; // intialize variables
	for(int i=0;i<graph_size;++i) {
		augment_path_in[i] = 0;
	}
	return dfs_augment(pos);
}

void makeMatching()
{
	graph_size = size*2 + 2;
	for(int i=0;i<graph_size;++i) {
		for(int j=0;j<graph_size;++j) {
			graph[i][j] = 0;
		}
	}
	for(int i=0;i<size;++i) { // build graph
		graph[0][1+i] = 1; // from src to i
		graph[1+size+i][graph_size-1] = 1; // from i to sink
		for(int j=0;j<size;++j) {
			graph[1+i][1+size+j] = (xlabel[i] + ylabel[j] == cost[i][j] ? 1 : 0); // equality check
		}
	}
	// Ford Fulkerson -> maximum matching
	while(find_augment(0) == 1) { // until no augment
		for(int i=1;i<augment_path_idx;++i) {
			int left = augment_path[i-1];
			int right = augment_path[i];
			graph[left][right] = 0; // reverse
			graph[right][left] = 1;
		}
	}
	// matching
	for(int i=0;i<size;++i) {
		matching[i] = -1;
		matching_reverse[i] = -1;
	}
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(graph[1+size+j][1+i] == 1) {
				matching[i] = j;
				matching_reverse[j] = i;
				break;
			}
		}
	}
}

void labelInitialize()
{
	for(int i=0;i<size;++i) {
		ylabel[i] = 0; // all label-y is zero
		int max = -1;
		for(int j=0;j<size;++j) {
			if(max < cost[i][j]) { // label-x is minimum value of weight of connected edge
				max = cost[i][j];
			}
		}
		xlabel[i] = max;
	}
}

void makeCost()
{
	int wb[250];
	int bw[250];
	int wb_idx = 0;
	int bw_idx = 0;
	for(int i=0;i<n;++i) {
		if(color[i] == 0 && token[i] == 1) {
			wb[wb_idx++] = i; // choose that color is white and token is black
		}
		else if(color[i] == 1 && token[i] == 0) {
			bw[bw_idx++] = i; // choose that color is black and token is white
		}
	}
	for(int i=0;i<wb_idx;++i) {
		int now_wb = wb[i];
		for(int j=0;j<bw_idx;++j) {
			int now_bw = bw[j]; // build cost matrix with what color and token are different
			cost[i][j] = net[now_wb][now_bw];
		}
	}
	size = wb_idx;
}

void FloydWarshall()
{
	for(int k=0;k<n;++k) for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
		int newval = net[i][k] + net[k][j]; if(newval < net[i][j]) {
			net[i][j] = newval;
		} 
	}
}

void getInput()
{
	cin >> n >> m;
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			net[i][j] = INFINITE; // Initialize maximum
		}
	}
	for(int i=0;i<m;++i) {
		int left, right;
		cin >> left >> right;
		--left;--right;
		net[left][right] = 1;
		net[right][left] = 1;
	}
	for(int i=0;i<n;++i) cin >> color[i];
	for(int i=0;i<n;++i) cin >> token[i];
}

void DO()
{
	getInput(); // get input 
	FloydWarshall(); // calculate minimum costs
	makeCost(); // build cost matrix
	labelInitialize(); // trivial label setting
	makeMatching(); // maximum matching
	while(perfect_matching() == false) { // check perfect matching
		int u = STInitialize(); // Initialize S, T
		updateNl(); // Calculate N_l(s)
		int augmented = 0;
		while(!(NlEqualToT())) { // Check N_l(s) == T
			int y = pickY(); // pick y in (N_l(s) - T)
			int z = matching_reverse[y];
			if(z == -1) { // y is free -> augment exists
				augmented = 1;
				makeMatching(); // Re-matching
				break;
			} else { // y is matched with z
				S_array[S_idx++] = z; // append z to S
				S_check[z] = 1;
				T_array[T_idx++] = y; // append y to T
				T_check[y] = 1;
				updateNl(); // Re-calculate N_l(s)
			}
		}
		if(augmented) continue;
		updateLabel(); // update Labels
	}
	int result = 0;
	for(int i=0;i<size;++i) {
		if(matching[i] == -1) {
			cout << "Error" << endl;
			break;
		}
		result += cost[i][matching[i]];
	}
	cout << result << endl;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int i=0;i<T;++i) {
		DO();
	}
	return 0;
}