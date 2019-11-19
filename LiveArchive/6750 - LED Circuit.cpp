#include <iostream>
using namespace std;

#define MAXM 8192
#define MAXN 512
#define INF 1000000000

int f[MAXN], d[MAXN];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

struct edge {
	int a, b, w;
} e[2*MAXM+MAXN];

int main() {
	int N, M, W, m[2][MAXM], i, j, a, b, minv, maxv, C, E;
	
	while (cin >> N >> M >> W >> minv >> maxv && N+M+W+minv+maxv > 0) {
		for (i=1; i<=N; i++) { f[i] = i; d[i] = INF; }
		for (i=0; i<M; i++) cin >> m[0][i] >> m[1][i];
		for (i=0; i<W; i++) {
			cin >> a >> b;
			f[getf(a)] = getf(b);
		}
		
		d[0] = C = E = 0;
		for (i=1; i<=N; i++) if (getf(i) == i) {
			e[E].a = e[E].w = 0;
			e[E++].b = i;
			C++;
		}
		
		for (i=0; i<M; i++) {
			a = getf(m[0][i]); b = getf(m[1][i]);
			e[E].a = a; e[E].b = b;
			e[E++].w = maxv;
			e[E].a = b; e[E].b = a;
			e[E++].w = -minv;
		}
		
		for (i=0; i<C-1; i++) for (j=0; j<E; j++) d[e[j].b] = min(d[e[j].b], d[e[j].a]+e[j].w);
		
		for (j=0; j<E; j++) if (d[e[j].b] > d[e[j].a]+e[j].w) break;
		if (j < E) cout << "Impossible" << endl;
		else {
			j = 0;
			for (i=1; i<=N; i++) if (getf(i) == i) j = min(j, d[i]);
			cout << -j << endl;
		}
	}

	return 0;
}
