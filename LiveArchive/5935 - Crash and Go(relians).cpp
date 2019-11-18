#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 128
#define SQ(x) ( (x)*(x) )

typedef double tint;

struct pt {
	tint x, y;
	pt(tint _x=0.0, tint _y=0.0) {
		x=_x; y=_y;
	}
};

pt operator+(const pt &p1, const pt &p2) {
	return pt(p1.x+p2.x, p1.y+p2.y);
}

pt operator/(const pt &p, const tint &v) {
	return pt(p.x/v, p.y/v);
}

tint dist(const pt &p1, const pt &p2) {
	return sqrt(SQ(p1.x-p2.x) + SQ(p1.y-p2.y));
}

struct circ {
	pt p;
	tint r;
} n[MAXN];

int f[MAXN];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

int join(int N) {
	int i, j, c[MAXN], curf;
	tint r[MAXN];
	pt p[MAXN];
	
	for (i=0; i<N; i++) { f[i] = i; c[i] = 0; r[i] = 0.0; p[i] = pt(0.0, 0.0); }
	for (i=0; i<N; i++) for (j=i+1; j<N; j++) if (dist(n[i].p, n[j].p) < max(n[i].r, n[j].r)) f[getf(i)] = getf(j);
	for (i=0; i<N; i++) {
		curf = getf(i);
		c[curf]++;
		r[curf] += SQ(n[i].r);
		p[curf] = p[curf] + n[i].p;
	}
	for (i=j=0; i<N; i++) if (getf(i) == i) {
		n[j].p = p[i]/c[i];
		n[j].r = sqrt(r[i]);
		j++;
	}
	return j;
}

int main() {
	int N, M, i, tmp;
	tint X, Y, R;
	
	while (cin >> N && N) {
		
		M = 0;
		for (i=0; i<N; i++) {
			cin >> n[M].p.x >> n[M].p.y >> n[M].r; M++;
			while (tmp = join(M)) {
				if (tmp == M) break;
				M = tmp;
			}
		}
		cout << M << endl;
	}

	return 0;
}
