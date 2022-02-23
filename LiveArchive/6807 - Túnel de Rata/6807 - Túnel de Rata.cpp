#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 16384
#define MAXE 131072

struct edge {
	int a, b, w;
} m[MAXE];

bool operator<(const edge &e1, const edge &e2) {
	if (e1.w != e2.w) return e1.w > e2.w;
	else if (e1.a != e2.a) return e1.a < e2.a;
	else return e1.b < e2.b;
}

int f[MAXN];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

int main() {
	int T, t, N, M, i, TOT, fa, fb, RES;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N >> M;
		
		TOT = 0;
		for (i=0; i<M; i++) {
			cin >> m[i].a >> m[i].b >> m[i].w;
			TOT += m[i].w;
		}
		sort(m,m+M);
		
		RES = -1;
		for (i=1; i<=N; i++) f[i] = i;
		for (i=0; i<M; i++) {
			fa = getf(m[i].a); fb = getf(m[i].b);
			if (fa != fb) {
				f[fa] = fb;
				TOT -= m[i].w;
			} else RES = max(RES, m[i].w);
		}
		
		cout << "Case #" << t << ": " << TOT << ' ' << RES << endl;
	}

	return 0;
}
