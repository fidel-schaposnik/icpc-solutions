#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 2048
#define MAXK 32

int n[MAXN], dp[MAXN][MAXK];

int cost(int a, int b) {
	int tmp = (n[b]-n[a-1])%10;
	if (tmp <= 4) return n[b]-n[a-1] - tmp;
	else return n[b]-n[a-1] + 10-tmp;
}

int _dp(int p, int k) {
	if (dp[p][k] == -1) {
		dp[p][k] = cost(1,p);
		if (k) for (int i=1; i<=p; i++) dp[p][k] = min(dp[p][k], _dp(i-1, k-1)+cost(i,p));
	}
	return dp[p][k];
}

int main() {
	int N, K, i;
	
	while(cin >> N >> K) {
		for (i=1; i<=N; i++) cin >> n[i];
		for (i=1; i<=N; i++) n[i] += n[i-1];
			
		memset(dp, -1, sizeof(dp));
		for (i=0; i<K; i++) dp[0][i] = 0;
		cout << _dp(N, K) << endl;
	}

	return 0;
}
