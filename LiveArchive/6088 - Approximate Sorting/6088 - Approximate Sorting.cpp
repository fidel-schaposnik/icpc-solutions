#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAXN 18
#define INF 1000000

int dp[1<<MAXN], N, _prev[1<<MAXN];
string n[MAXN];

bool cmp(int i, int j) {
	return n[i][j]=='1';
}

int _dp(int mask) {
	if (dp[mask] == -1) {
		dp[mask] = INF;
		for (int i=0; i<N; i++) if ((mask>>i)&1) {
			int tmp = 0;
			for (int j=0; j<N; j++) if (((mask>>j)&1) == 0 && cmp(i,j)) tmp++;
			if (_dp(mask^(1<<i))+tmp < dp[mask]) {
				dp[mask] = _dp(mask^(1<<i))+tmp;
				_prev[mask] = mask^(1<<i);
			}
		}
	}
	return dp[mask];
}

void print(int mask) {
	for (int i=0; i<N; i++) if (((_prev[mask]^mask)>>i)&1) cout << i;
	if (_prev[mask]) {
		cout << ' ';
		print(_prev[mask]);
	} else cout << endl;
}

int main() {
	int i;
	
	while (cin >> N && N) {
		for (i=0; i<N; i++) cin >> n[i];
		
		memset(dp, -1, sizeof(dp)); dp[0] = 0;
		_dp((1<<N)-1); print((1<<N)-1);
		cout << dp[(1<<N)-1] << endl;
	}

	return 0;
}
