#include <iostream>
using namespace std;

typedef unsigned long long tint;

#define MAXN 131072
#define LOGMAXN 18

tint n[MAXN], g[MAXN][LOGMAXN];

tint gcd(tint a, tint b) {
	if (b == 0ULL) return a;
	else return gcd(b, a%b);
}

void init(int N) {
	for (int i=0; i<N; i++) g[i][0] = n[i];
	for (int j=1; (1<<j)<=N; j++) for (int i=0; i+(1<<j)<=N; i++) g[i][j] = gcd(g[i][j-1], g[i+(1<<(j-1))][j-1]);
}

tint query(int s, int e) {
    int k = 31 - __builtin_clz(e-s);
    return gcd(g[s][k], g[e-(1<<k)][k]);
}

int get(int start, int s, int e, tint cur) {
	while (e-s > 1) {
		int m = (s+e)/2;
		if (query(start, m) == cur) s = m;
		else e = m;
	}
	return s;
}

int main() {
	int T, t, N, i, j, cur;
	tint curg, RES;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=0; i<N; i++) cin >> n[i];
		n[N++] = 1ULL;
		
		init(N);
		RES = N-1;
		for (i=0; i<N; i++) {
			cur = i; curg = n[i];
			while (cur < N && curg > 1ULL) {
				j = get(i, cur, N, curg);
				RES = max(RES, (j-i)*curg);
				cur = j; curg = query(i,j+1);
			}
		}
		cout << RES << endl;
	}

	return 0;
}
