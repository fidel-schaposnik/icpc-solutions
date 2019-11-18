#include <iostream>
#include <vector>
using namespace std;

#define MAXC 64
#define MAXN 64*64
#define MAXE 64*64*4
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

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
	int T=1, R, C, i, j, N, num[MAXN][MAXC], SOURCE, SINK;
	char m[MAXC][MAXC];
	
	while (cin >> R >> C && R && C) {
		
		N = 0;
		for (i=1; i<=R; i++) for (j=1; j<=C; j++) {
			cin >> m[i][j];
			if (m[i][j] == '#') num[i][j] = N++;
		}
		for (i=1; i<=R; i++) m[i][0] = m[i][C+1] = '.';
		for (j=1; j<=C; j++) m[0][j] = m[R+1][j] = '.';

		SOURCE = N++; SINK = N++;
		init(N);
		for (i=1; i<=R; i++) for (j=1; j<=C; j++) if (m[i][j] == '#') {
			if ((i+j)%2) {
				add_edge(SOURCE, num[i][j], 1, 0);
				for (int k=0; k<4; k++) if (m[i+dx[k]][j+dy[k]] =='#') add_edge(num[i][j], num[i+dx[k]][j+dy[k]], 1, 0);
			} else add_edge(num[i][j], SINK, 1, 0);
		}
		
		cout << "Case " << T++ << ": ";
		if (N%2 || dinic(N, SOURCE, SINK) < (N-2)/2) cout << "Impossible" << endl;
		else cout << "Possible" << endl;
	}

	return 0;
}
