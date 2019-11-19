#include <iostream>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 256

int n[2*MAXN];
char s[2*MAXN];
bool done[2*MAXN][2*MAXN];
pair<long long, long long> dp[2*MAXN][2*MAXN];

pair<long long, long long> _dp(int a, int b) {
	if (!done[a][b]) {
		pair<long long, long long> tmp1, tmp2;
		dp[a][b] = make_pair(LLONG_MAX, LLONG_MIN);
		for (int i=a+1; i<b; i++) {
			tmp1 = _dp(a,i); tmp2 = _dp(i,b);
			if (s[i-1] == '+' || s[i-1] == '?') {
				dp[a][b].first = min(dp[a][b].first, tmp1.first+tmp2.first);
				dp[a][b].second = max(dp[a][b].second, tmp1.second+tmp2.second);
			}
			if (s[i-1] == '-' || s[i-1] == '?') {
				dp[a][b].first = min(dp[a][b].first, tmp1.first-tmp2.second);
				dp[a][b].second = max(dp[a][b].second, tmp1.second-tmp2.first);
			}
			if (s[i-1] == '*' || s[i-1] == '?') {
				dp[a][b].first = min(dp[a][b].first, min(min(tmp1.first*tmp2.first, tmp1.first*tmp2.second), min(tmp1.second*tmp2.first, tmp1.second*tmp2.second)));
				dp[a][b].second = max(dp[a][b].second, max(max(tmp1.first*tmp2.first, tmp1.first*tmp2.second), max(tmp1.second*tmp2.first, tmp1.second*tmp2.second)));
			}
		}
		done[a][b] = true;
	}
	return dp[a][b];
}

int main() {
	int N, i;
	
	while (cin >> N) {
		for (i=0; i<N; i++) {
			cin >> n[i] >> s[i];
			n[i+N] = n[i]; s[i+N] = s[i];
		}
		
		memset(done, false, sizeof(done));
		for (i=0; i<2*N; i++) {
			done[i][i+1] = true;
			dp[i][i+1] = make_pair(n[i], n[i]);
		}
		for (i=0; i<N; i++) printf("%lld%lld", abs(_dp(i,i+N).first), abs(_dp(i,i+N).second));
		cout << endl;
	}

	return 0;
}
