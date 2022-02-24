#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 65536
#define MAXE 262144

int x[MAXN], y[MAXN], w[MAXN], h[MAXN], f[MAXN], r[MAXN], a[MAXN];

struct event {
	int pos, v, id;
	bool type;
} e[MAXE];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

void join(int a, int b) {
	int fa = getf(a), fb = getf(b);
	if (r[fa] > r[fb]) f[fb] = f[fa];
	else if (r[fa] < r[fb]) f[fa] = f[fb];
	else { f[fb] = f[fa]; r[fa]++; }
}

bool operator<(const event &e1, const event &e2) {
	if (e1.pos != e2.pos) return e1.pos < e2.pos;
	else if (e1.v != e2.v) return e1.v < e2.v;
	else return e1.type;
}

int main() {
	int N, i, E, cur, cant, RES;
	
	while (cin >> N) {
		for (i=0; i<N; i++) {
			cin >> x[i] >> y[i] >> w[i] >> h[i];
			f[i] = i; r[i] = a[i] = 0;
		}
		
		E = 0;
		for (i=0; i<N; i++) {
			e[E].pos = e[E+1].pos = x[i];
			e[E+2].pos = e[E+3].pos = x[i]+w[i];
			e[E].id = e[E+1].id = e[E+2].id = e[E+3].id = i;
			e[E].v = e[E+2].v = y[i]; e[E+1].v = e[E+3].v = y[i]+h[i];
			e[E].type = e[E+2].type = true; e[E+1].type = e[E+3].type = false;
			E += 4;
		}
		
		sort(e,e+E); cur = cant = 0;
		for (i=0; i<E; i++) {
			if (e[i].type) {
				if (cant) join(cur, e[i].id);
				else cur = e[i].id;
				cant++;
			} else cant--;
		}
		
		E = 0;
		for (i=0; i<N; i++) {
			e[E].pos = e[E+1].pos = y[i];
			e[E+2].pos = e[E+3].pos = y[i]+h[i];
			e[E].id = e[E+1].id = e[E+2].id = e[E+3].id = i;
			e[E].v = e[E+2].v = x[i]; e[E+1].v = e[E+3].v = x[i]+w[i];
			e[E].type = e[E+2].type = true; e[E+1].type = e[E+3].type = false;
			E += 4;
		}
		
		sort(e,e+E); cur = -1; cant = 0;
		for (i=0; i<E; i++) {
			if (e[i].type) {
				if (cant) join(cur, e[i].id);
				else cur = e[i].id;
				cant++;
			} else cant--;
		}
		
		for (i=0; i<N; i++) a[getf(i)] += w[i]*h[i];
		
		RES = 0;
		for (i=0; i<N; i++) RES = max(RES, a[i]);
		cout << RES << endl;
	}

	return 0;
}
