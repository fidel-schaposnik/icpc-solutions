#include <iostream>
#include <vector>
using namespace std;

/* FLOW */

#define MAXD 512

#define MAXN 524288
#define MAXE 1048576
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
	for (int i=0; i<EDGES; i++) e[i].f = 0;

	int FLOW = 0;
	while (bfs(r, N, SOURCE, SINK)) FLOW += dfs(r, SOURCE, SINK, SOURCE, INF);
	return FLOW;
}

int b[MAXD][MAXD], w[MAXD][MAXD];
char m[MAXD][MAXD];

int main() {
	int T, t, N, M, i, j, B, W, SOURCE, SINK;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> M; B = W = 0;
		for (i=1; i<=N; i++) for (j=1; j<=M; j++) {
			cin >> m[i][j];
			if (m[i][j] == 'B') b[i][j] = B++;
			else if (m[i][j] == 'W') w[i][j] = W++;
		}
		for (i=0; i<=N+1; i++) m[i][0] = m[i][M+1] = '.';
		for (j=0; j<=M+1; j++) m[0][j] = m[N+1][j] = '.';
		
		if (2*B == W) {
			init(2*B+W+2); SOURCE = 2*B+W; SINK = 2*B+W+1;
			for (i=1; i<=N; i++) for (j=1; j<=M; j++) {
				if (m[i][j] == 'B') {
					add_edge(SOURCE, b[i][j], 1, 0);
					add_edge(SOURCE, b[i][j]+B, 1, 0);
					for (int k=-1; k<=1; k+=2) {
						if (m[i+k][j] == 'W') add_edge(b[i][j], w[i+k][j]+2*B, 1, 0);
						if (m[i][j+k] == 'W') add_edge(b[i][j]+B, w[i][j+k]+2*B, 1, 0);
					}
				} else if (m[i][j] == 'W') add_edge(w[i][j]+2*B, SINK, 1, 0);
			}
			if (dinic(2*B+W+2, SOURCE, SINK) == W) cout << "YES" << endl;
			else cout << "NO" << endl;
		} else cout << "NO" << endl;
	}

	return 0;
}
