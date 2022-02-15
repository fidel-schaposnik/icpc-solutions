#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 16
#define INF 1000000

bool is_substr(string &a, string &b) {
	for (int i=0; i+(int)a.size()<=(int)b.size(); i++) if (b.substr(i, a.size()) == a) return true;
	return false;
}

bool cmp(const string &s1, const string &s2) {
	if (s1.size() != s2.size()) return s1.size() > s2.size();
	else return s1 < s2;
}

int c[MAXN][MAXN], dp[1<<MAXN][MAXN], M;

int _dp(int m, int last) {
	if (dp[m][last] == -1) {
		dp[m][last] = INF;
		for (int i=0; i<=M; i++) if (i != last && ((m>>i)&1) == 1)
			dp[m][last] = min(dp[m][last], _dp(m^(1<<last), i)+c[i][last]);
	}
	return dp[m][last];
}

int main() {
	int N, i, j, k, RES;
	string s[MAXN], sp[MAXN];
	
	while (cin >> N && N) {
		for (i=0; i<N; i++) cin >> s[i];
		sort(s, s+N, cmp);
		
		M = 0;
		for (i=0; i<N; i++) {
			for (j=0; j<M; j++) if (is_substr(s[i], sp[j])) break;
			if (j == M) sp[M++] = s[i];
		}
		
		for (i=0; i<M; i++) {
			c[M][i] = (int)sp[i].size();
			for (j=0; j<M; j++) {
				for (k=(int)min(sp[i].size(), sp[j].size()); k>0; k--) if (sp[i].substr((int)sp[i].size()-k, k) == sp[j].substr(0, k)) break;
				c[i][j] = (int)sp[j].size()-k;
			}
		}
		
		memset(dp, -1, sizeof(dp)); dp[1<<M][M] = 0;
		RES = INF; for (i=0; i<M; i++) RES = min(RES, _dp((1<<(M+1))-1, i));
		cout << RES << endl;
	}

	return 0;
}
