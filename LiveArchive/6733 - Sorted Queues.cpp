#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 16384
#define INF 1000000

int n[2][MAXN], dp[MAXN][2];

int main() {
	int i, j, t, T, N;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=0; i<2; i++) for (j=0; j<N; j++) cin >> n[i][j];

		dp[0][0] = 0; dp[0][1] = 1;
		for (i=1; i<N; i++) {
			dp[i][0] = dp[i][1] = INF;
			if (n[0][i] > n[0][i-1] && n[1][i] > n[1][i-1]) {
				dp[i][0] = min(dp[i][0], dp[i-1][0]);
				dp[i][1] = min(dp[i][1], dp[i-1][1]+1);
			}
			if (n[0][i] > n[1][i-1] && n[1][i] > n[0][i-1]) {
				dp[i][0] = min(dp[i][0], dp[i-1][1]);
				dp[i][1] = min(dp[i][1], dp[i-1][0]+1);
			}
		}
		cout << ( min(dp[N-1][0], dp[N-1][1]) ==INF ? -1 : min(dp[N-1][0], dp[N-1][1]) ) << endl;
	}

	return 0;
}
