#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

#define MAXN 65536
#define EPS 1E-9
#define MAX 1048576

typedef int tint;

#define SQ(x) ( (x)*(x) )

int ox[MAXN], oy[MAXN], N, X, Y, H, V, pos_bit[MAX];

struct pt {
	tint x, y;
} n[MAXN];

struct seg {
	tint pos;
	double a, b;
} v[MAXN], h[MAXN];

struct event {
	int type, id;
	double pos;
} e[3*MAXN];

bool operator<(const event &e1, const event &e2) {
	if (abs(e1.pos-e2.pos) > EPS) return e1.pos-e2.pos < 0.0;
	else if (e1.type != e2.type) return e1.type > e2.type;
	else return e1.id < e2.id;
}

set< pair<int, int> > p;

int get_cf(int idx, int *bit) {
	int cf = bit[0];
	while (idx > 0) {
	   cf += bit[idx];
		idx &= idx-1;
	}
	return cf;
}

void upd_f(int idx, int f, int *bit) {
	if (idx == 0) bit[idx] += f;
   else while (idx < MAXN) {
	   bit[idx] += f;
		idx += idx&(-idx);
	}
}

bool inter() {
	int i, E;

	E = 0;
	for (i=0; i<H; i++) {
		e[E].pos = h[i].b;
		e[E].id = i;
		e[E++].type = 1;
		
		e[E].pos = h[i].a;
		e[E].id = i;
		e[E++].type = -1;
	}
	for (i=0; i<V; i++) {
		e[E].pos = v[i].pos;
		e[E].id = i;
		e[E++].type = 0;
	}
	sort(e, e+E);
	
	memset(pos_bit,0,sizeof(pos_bit));
	for (i=0; i<E; i++) {
		if (e[i].type) upd_f(h[e[i].id].pos+1, e[i].type, pos_bit);
		else if (get_cf(floor(v[e[i].id].a)+1, pos_bit)-get_cf(ceil(v[e[i].id].b), pos_bit)) return true;
	}
	return false;
}

bool check(double l) {
	int i, last, cur;
	set< pair<int, int> >::iterator it;
	double a, b;
	
	p.clear(); last = V = 0;
	for (i=0; i<N; i++) {
		cur = ox[i];
		while (n[cur].x+l-EPS < n[ox[last]].x) { p.erase(make_pair(n[ox[last]].y, ox[last])); last++; }
		it = p.upper_bound(make_pair(n[cur].y, N));
		if (it == p.end()) a = Y-2.0*l;
		else a = it->first-2.0*l;
		if (it != p.begin()) { it--; b = it->first; }
		else b = 0.0;
		p.insert(make_pair(n[cur].y, cur));
		
		if (a+EPS > b) {
			v[V].a = a; v[V].b = b;
			v[V++].pos = n[cur].x;
		}
	}
	
	p.clear(); last = H = 0;
	for (i=0; i<N; i++) {
		cur = oy[i];
		while (n[cur].y+l-EPS < n[oy[last]].y) { p.erase(make_pair(n[oy[last]].x, oy[last])); last++; }
		it = p.upper_bound(make_pair(n[cur].x, N));
		if (it == p.end()) a = X-2.0*l;
		else a = it->first-2.0*l;
		if (it != p.begin()) { it--; b = it->first; }
		else b = 0.0;
		p.insert(make_pair(n[cur].x, cur));
		
		if (a+EPS > b) {
			h[H].a = a; h[H].b = b;
			h[H++].pos = n[cur].y;
		}
	}
	return inter();
}

bool cmp_x(const int &a, const int &b) {
	if (n[a].x != n[b].x) return n[a].x > n[b].x;
	else return n[a].y > n[b].y;
}

bool cmp_y(const int &a, const int &b) {
	if (n[a].y != n[b].y) return n[a].y > n[b].y;
	else return n[a].x > n[b].x;
}

int main() {
	double s, e, m;
	
	while (cin >> N >> X >> Y && (N!=0 || X!=0 || Y!=0)) {
		n[0].x = n[0].y = ox[0] = oy[0] = 0;
		for (int i=1; i<=N; i++) {
			cin >> n[i].x >> n[i].y;
			ox[i] = oy[i] = i;
		}
		N++;
		sort(ox, ox+N, cmp_x);
		sort(oy, oy+N, cmp_y);
		
		s = 0.0; e = min(X,Y)/2.0;
		while (e-s > EPS) {
			m = (s+e)/2.0;
			if (check(m)) s = m;
			else e = m;
		}
		printf("%.2lf\n", 3.0*SQ((s+e)/2.0));
	}

	return 0;
}
