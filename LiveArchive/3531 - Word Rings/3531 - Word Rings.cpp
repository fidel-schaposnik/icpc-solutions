#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define MAXN 1024
#define MAXE 131072
#define EPS 1E-9

int get(char a, char b) {
	return (a-'a')*26 + b-'a';
}

struct edge {
	int a, b, w;
} e[MAXE];

bool v[MAXN];
double d[MAXN];

bool check(double w, int N, int E) {
	memset(d, 0.0, sizeof(d));
	for (int j=0; j<N; j++) for (int i=0; i<E; i++) {
		double tmpw = w-e[i].w;
		d[e[i].a] = min(d[e[i].a], d[e[i].b]+tmpw);
	}
	for (int i=0; i<E; i++) {
		double tmpw = w-e[i].w;
		if (d[e[i].a] > d[e[i].b]+tmpw) return true;
	}
	return false;
}

int main() {
	int N, E, i, TMP, NN;
	char tmp[MAXN];
	double l, r, m;
	
	while (scanf("%d", &N) != EOF && N!=0) {
		memset(v, false, sizeof(v)); E = 0;
		for (i=0; i<N; i++) {
			scanf("%s", tmp); TMP = strlen(tmp);
			if (TMP <= 2) continue;
			
			e[E].a = get(tmp[0], tmp[1]);
			e[E].b = get(tmp[TMP-2], tmp[TMP-1]);
			v[e[i].a] = v[e[i].b] = true;
			e[E++].w = TMP;
		}
		
		NN = 0;
		for (i=0; i<MAXN; i++) if (v[i]) NN++;
		
		l = r = 0.0;
		for (i=0; i<E; i++) r = max(r, (double)e[i].w);
		while (r-l > EPS) {
			m = (l+r)/2.0;
			if (check(m, NN, E)) l = m;
			else r = m;
		}
		printf("%.2lf\n", (l+r)/2.0);
	}

	return 0;
}
