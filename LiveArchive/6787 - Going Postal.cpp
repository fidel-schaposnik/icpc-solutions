#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define MAXN 20
#define INF 1000000000

int dp[1<<MAXN][MAXN], x[MAXN], y[MAXN], N, W, H, RES;

int _dp(int m, int l) {
	if (dp[m][l] == -1) {
		dp[m][l] = INF;
		for (int i=0; i<N; i++)
			if (i != l && (m>>i)&1)
				dp[m][l] = min(dp[m][l], _dp(m^(1<<l), i)+W*abs(x[i]-x[l])+H*abs(y[i]-y[l]));
	}
	return dp[m][l];
}

void dfs(int pos, int m, int cant) {
	if (pos < N) {
		dfs(pos+1, m, cant);
		if (cant) dfs(pos+1, m^(1<<pos), cant-1);
	} else if (!cant) {
		for (int i=0; i<N; i++) if ((m>>i)&1) {
			RES = min(RES, _dp(m, i)+_dp(((1<<N)-1)^m^1^(1<<i), i));
		}
	}
}

int main() {
	int S, D, T, t, i;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N >> W >> H >> S >> D;
		for (i=0; i<N; i++) cin >> x[i] >> y[i];
		
		memset(dp, -1, sizeof(dp));
		for (i=0; i<N; i++) dp[1<<i][i] = W*abs(x[i]-x[0])+H*abs(y[i]-y[0]);
		if (N <= 2) RES = _dp((1<<N)-1, 0)/S+N*D;
		else {RES = INF; dfs(1, 0, N/2); RES = RES/S+N*D;}
		printf("%02d:%02d\n", (18+RES/60)%24, RES%60);
	}	

	return 0;
}
