#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 262144
#define MAXK 16

int dp[MAXN][MAXK];

struct obj {
	int v, c;
} n[MAXN];

bool operator<(const obj &o1, const obj &o2) {
	return o1.v < o2.v;
}

int _dp(int cur, int k) {
	if (dp[cur][k] == -1) {
		int tmp = n[cur].v-n[cur].c;
		if (k) tmp = min(tmp, _dp(cur+1,k-1)-n[cur].c);
		dp[cur][k] = max(_dp(cur+1,k), tmp);
	}
	return dp[cur][k];
}

int main() {
	int T, t, N, K, i, j;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> K;
		for (i=0; i<N; i++) cin >> n[i].v >> n[i].c;
		sort(n,n+N);
		
		memset(dp, -1, sizeof(dp));
		for (i=0; i<MAXK; i++) dp[N][i] = 0;
		cout << _dp(0, K) << endl;
	}

	return 0;
}
