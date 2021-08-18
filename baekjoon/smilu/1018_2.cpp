#include <bits/stdc++.h>
using namespace std;

int n, m;
char b[51][51];
int s[51][51];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m; // Read (width, height) of board
	for (int i = 0; i < n; i++) cin >> b[i]; // Read each rows of board
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			// 'W' is 87 (0b1010111)
			// 'B' is 66 (0b1000010)
			b[i][j] &= 1; // b[i][j] hold 1 if it was 'W', else 0
			
			// 010101
			// 101010
			// 010101
			// 101010
			// In chess grid pattern, sum of the elements of coordinate (x, y)
			// of the grid is odd number if its colors is white

			// Invert b[i][j] values of white grids
			// if (i + j) is odd number, then grid (i, j) is white
			if (((i + j) & 1)) b[i][j] = !b[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			// s[i][j] should hold sum of the b[k][l] (0 <= k < i, 0 <= l < j)
			// s[i][j] can be dynamically calculated with simple inclusion-exclusion principle
			//   (inclusion-exclusion principle => P(A + B) = P(A) + P(B) - P(AB)
			// In this case, P(A) = s[i][j-1], P(B) = s[i-1][j], P(AB) = s[i-1][j-1]
			//   P(A + B) = sum of the b[k][l] (0 <= k < i, 0 <= l < j), except b[i-1][j-1]
			s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + b[i-1][j-1];
		}
	}
	int ans = 0x3f3f3f3f; // arbitrary large number (1061109567)
	for (int i = 0; i <= n-8; i++) {
		for (int j = 0; j <= m-8; j++) {
			int k = i + 8, l = j + 8;
			
			// the required number of change on board are now sum of the
			// [b[i][j] ~ b[i+8][j+8]) (box shape) 64 components
			// , or 64 minus this.
			
			// sum of the [b[i][j] ~ b[i+8][j+8]) can also be calculated
			// with a simple inclusion-exclusion principle
			int sum = s[k][l] - s[k][j] - s[i][l] + s[i][j];
			int loc = min(sum, 64 - sum);
			ans = min(ans, loc);
		}
	}
	cout << ans << '\n';
}
