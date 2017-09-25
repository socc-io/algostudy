#include <vector>

using namespace std;

#define INF (0x7FFFFFFF)

vector<vector<int>> *p_data;
int S[5000][5000];
int x_sort[5000];
int y_sort[5000];
pair<int, int> ranking[5000];
int N;

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

bool compare_x(int a, int b)
{
	return (*p_data)[a][0] < (*p_data)[b][0];
}
bool compare_y(int a, int b)
{
	return (*p_data)[a][1] < (*p_data)[b][1];
}

int solution(int n, vector<vector<int>> data)
{
	p_data = &data;
	N = data.size();
	for(int i = 0; i < N; ++i) {
		x_sort[i] = i;
		y_sort[i] = i;
		for(int j = 0; j < N; ++j) S[i][j] = 0;
	}
	sort(x_sort, x_sort + N, compare_x);
	sort(y_sort, y_sort + N, compare_y);
	for(int i = 0; i < N; ++i) {
		ranking[x_sort[i]].first = i;
		ranking[y_sort[i]].second = i;
	}
	for(int i = 0; i < N; ++i) {
		S[ranking[i].first][ranking[i].second] = 1;
	}

	for(int i = 1; i < N; ++i) {
		S[i][0] += S[i-1][0];
		S[0][i] += S[0][i-1];
	}
	for(int i = 1; i < N; ++i) {
		for(int j = 1; j < N; ++j) {
			S[i][j] += S[i-1][j] + S[i][j-1] - S[i-1][j-1];
		}
	}

	int ans = 0;
	for(int i = 0; i < N; ++i) {
		for(int j = i + 1; j < N; ++j) {
			if(data[i][0] == data[j][0] || data[i][1] == data[j][1]) continue;
			int X = max(ranking[i].first, ranking[j].first) - 1;
			int x = min(ranking[i].first, ranking[j].first);
			int Y = max(ranking[i].second, ranking[j].second) - 1;
			int y = min(ranking[i].second, ranking[j].second);
			int tmp = S[X][Y] + S[x][y] - S[x][Y] - S[y][X];
			ans += tmp == 0;
			// printf("(%d, %d) tmp: %d\n", i, j, tmp);
		}
	}

	return ans;
}