#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 512
#define MAXE 65536

struct edge {
	int a, b, w;
} m[MAXE];

bool operator<(const edge &e1, const edge &e2) {
	if (e1.w != e2.w) return e1.w < e2.w;
	else if (e1.a != e2.a) return e1.a < e2.a;
	else return e1.b < e2.b;
}

int N, M, f[MAXN];
bool ref[MAXE], tmp[MAXE];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

int mst(int skip, bool used[]) {
	int i, fa, fb, RES = 0;
	
	for (i=1; i<=N; i++) f[i] = i;
	for (i=0; i<M; i++) if (i != skip) {
		fa = getf(m[i].a); fb = getf(m[i].b);
		if (fa != fb) {
			f[fa] = fb;
			used[i] = true;
			RES += m[i].w;
		} else used[i] = false;
	}
	return RES;
}

int main() {
	int i, cost, CANT, RES;
	
	while (cin >> N >> M) {
		for (i=0; i<M; i++) cin >> m[i].a >> m[i].b >> m[i].w;
		sort(m, m+M);
		
		cost = mst(-1, ref); CANT = N-1; RES = 0;
		for (i=0; i<M; i++) if (ref[i]) {
			if (mst(i, tmp) == cost) CANT--;
			else RES += m[i].w;
		}
		cout << CANT << ' ' << RES << endl;
	}
	
	return 0;
}
