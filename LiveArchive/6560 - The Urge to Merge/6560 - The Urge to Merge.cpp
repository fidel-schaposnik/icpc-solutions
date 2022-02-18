#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1024
#define INF 1000000000

int n[3][MAXN], dp[MAXN][8];

int _dp(int cur, int m) {
	if (dp[cur][m] == -1) {
		for (int i=0; i<8; i++) if ((i&m) == 0) {
			int tmp = 0;
			if ((m^i) == 0) tmp = n[1][cur]*max(n[0][cur], n[2][cur]);
			else {
				for (int j=0; j<3; j++) if ((i>>j)&1) tmp += n[j][cur]*n[j][cur+1];
				if (((m^i)&3) == 0) tmp += n[0][cur]*n[1][cur];
				else if (((m^i)&6) == 0) tmp += n[1][cur]*n[2][cur];
			}
			dp[cur][m] = max(dp[cur][m], _dp(cur+1,i)+tmp);
		}
	}
	return dp[cur][m];
}

int main() {
	int N, i, j, t = 1;
	
	while (cin >> N && N) {
		for (i=0; i<3; i++) for (j=0; j<N; j++) cin >> n[i][j];
		
		memset(dp, -1, sizeof(dp));
		dp[N][0] = 0; for (i=1; i<8; i++) dp[N][i] = -INF;
		cout << "Case " << t++ << ": " << _dp(0, 0) << endl;
	}

	return 0;
}
