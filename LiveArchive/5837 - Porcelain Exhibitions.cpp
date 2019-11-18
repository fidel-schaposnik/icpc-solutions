#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

/* ============ START DINIC ============ */

#define MAXN 2048
#define MAXE 16384
#define INF 1000000000

#define OTHER(x, y) ( e[(x)].a == y ? e[(x)].b : e[(x)].a )
#define RESIDUAL(x, y) ( (y) == e[(x)].a ? e[(x)].cd-e[(x)].f : e[(x)].cr+e[(x)].f )

struct node {
	vector<int> c;
    int point;
} n[MAXN];

struct edge {
	int a, b, cd, cr, f;
} e[MAXE];

int EDGES;

void init(int N) {
	for (int i=0; i<N; i++) n[i].c.clear();
	EDGES = 0;
}

void add_edge(int a, int b, int cd, int cr) {
	e[EDGES].a = a; e[EDGES].b = b;
	e[EDGES].cd = cd; e[EDGES].cr = cr;
	n[e[EDGES].a].c.push_back(EDGES);
	n[e[EDGES].b].c.push_back(EDGES);
	e[EDGES].f = 0;//CUIDADO!!!
	EDGES++;
}

bool bfs(int *r, int N, int SOURCE, int SINK) {
	int i, S, E, s[MAXN], cur, next, cure;

	for (i=0; i<N; i++) {r[i] = -1; n[i].point = 0;} r[SOURCE] = 0;
	S = E = 0; s[E++] = SOURCE;
	while (S < E) {
		cur = s[S++];
		for (i=0; i<(int)n[cur].c.size(); i++) {
			cure = n[cur].c[i];
			next = OTHER(cure, cur);
			if (r[next] == -1 && RESIDUAL(cure, cur) > 0) {
				s[E++] = next;
				r[next] = r[cur]+1;
			}
		}
	}
	return r[SINK] != -1;
}

int dfs(int *r, int SOURCE, int SINK, int cur, int flowcap) {
	if (cur == SINK) return flowcap;

	int curflow = 0;
	for (; curflow<flowcap && n[cur].point<(int)n[cur].c.size(); n[cur].point++) {
		int cure = n[cur].c[n[cur].point];
		int next = OTHER(cure, cur);

		if (r[next] == r[cur]+1 && RESIDUAL(cure, cur) > 0) {
			int tmp = dfs(r, SOURCE, SINK, next, min(flowcap-curflow, RESIDUAL(cure, cur)));
			curflow += tmp;
			if (cur == e[cure].a) e[cure].f += tmp;
			else e[cure].f -= tmp;
		}
	}
	return curflow;
}

int dinic(int N, int SOURCE, int SINK) {
	int r[MAXN];
//	if (initialize) for (int i=0; i<EDGES; i++) e[i].f = 0;

	int FLOW = 0;
	while (bfs(r, N, SOURCE, SINK)) FLOW += dfs(r, SOURCE, SINK, SOURCE, INF);
	return FLOW;
}

/* ============ END DINIC ============ */

#define MAXP 1024
#define MAXM 16384

struct pt {
	int x, y;
	pt(int _x=0, int _y=0) {
		x=_x, y=_y;
	}
} p[MAXP];

pt operator-(const pt &p1, const pt &p2) {
	return pt(p1.x-p2.x, p1.y-p2.y);
}

int operator^(const pt &p1, const pt &p2) {
	return p1.x*p2.y-p1.y*p2.x;
}

struct frontera {
	int a, b, w;
} m[MAXM];

int CUR, next[MAXP][MAXP];
vector<int> adj[MAXP], points[MAXN];
map< pair<int,int>, int > border;

bool cmp(const int &a, const int &b) {
	return ((p[a]-p[CUR])^(p[b]-p[CUR])) > 0;
}

void dfs2(int cur, int prev, int p) {
	border[make_pair(prev, cur)] = p;
	points[p].push_back(cur);
	int tmp = next[cur][prev];
	if (border.find(make_pair(cur, tmp)) == border.end()) dfs2(tmp, cur, p);
}

int area(int prov) {
	int RES = 0;
	for (int i=1; i<points[prov].size()-1; i++) RES += (p[points[prov][i]] - p[points[prov][0]])^(p[points[prov][i+1]] - p[points[prov][0]]);
	return abs(RES);
}

int main() {
	int P, M, MIN, MAX, K, i, N, SOURCE, SINK, out, outsize, tmp;
	
	while (cin >> P >> M >> MIN >> MAX >> K && (P!=0 || M!=0 || MIN!=0 || MAX!=0 || K!=0)) {
		for (i=0; i<P; i++) {
			cin >> p[i].x >> p[i].y;
			adj[i].clear();
		}
		
		for (i=0; i<M; i++) {
			cin >> m[i].a >> m[i].b >> m[i].w;
			adj[m[i].a].push_back(m[i].b);
			adj[m[i].b].push_back(m[i].a);
		}
		
		for (CUR=0; CUR<P; CUR++) {
			sort(adj[CUR].begin(), adj[CUR].end(), cmp);
			for (i=0; i<adj[CUR].size()-1; i++) next[CUR][adj[CUR][i]] = adj[CUR][i+1];
			next[CUR][adj[CUR].back()] = adj[CUR][0];
		}
		
		N = 0; border.clear();
		for (i=0; i<M; i++) {
			if (border.find(make_pair(m[i].a, m[i].b)) == border.end()) { points[N].clear(); dfs2(m[i].b, m[i].a, N++); }
			if (border.find(make_pair(m[i].b, m[i].a)) == border.end()) { points[N].clear(); dfs2(m[i].a, m[i].b, N++); }
		}

		SOURCE = N; SINK = N+1; init(N+2);
		for (i=0; i<M; i++) if (m[i].w) add_edge(border[make_pair(m[i].a, m[i].b)], border[make_pair(m[i].b, m[i].a)], m[i].w, m[i].w);
		
		out = -1; outsize = 0;
		for (i=0; i<N; i++) {
			tmp = area(i);
			if (tmp > outsize) { out = i; outsize = tmp; }
			add_edge(SOURCE, i, K*tmp/2, 0);
		}
		for (i=0; i<N; i++) if (i != out) add_edge(i, SINK, MIN, 0);
		
		if (dinic(N+2, SOURCE, SINK) < (N-1)*MIN) cout << -1 << endl;
		else {
			for (i=0; i<N; i++) if (i != out) add_edge(i, SINK, MAX-MIN, 0);
			cout << MIN*(N-1) + dinic(N+2, SOURCE, SINK) << endl;
		}
	}
	
	return 0;
}
