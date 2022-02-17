#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 1048576
#define MAXE 2097152
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

int EDGES, RES, s[MAXN], r[MAXN];

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

bool bfs(int N, int SOURCE, int SINK) {
	int i, S, E, cur, next, cure;

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

int dfs(int SOURCE, int SINK, int cur, int flowcap) {
	if (cur == SINK) return flowcap;

	int curflow = 0;
	for (; curflow<flowcap && n[cur].point<(int)n[cur].c.size(); n[cur].point++) {
		int cure = n[cur].c[n[cur].point];
		int next = OTHER(cure, cur);

		if (r[next] == r[cur]+1 && RESIDUAL(cure, cur) > 0) {
			int tmp = dfs(SOURCE, SINK, next, min(flowcap-curflow, RESIDUAL(cure, cur)));
			curflow += tmp;
			if (cur == e[cure].a) e[cure].f += tmp;
			else e[cure].f -= tmp;
		}
	}
	return curflow;
}

int dinic(int N, int SOURCE, int SINK) {
	for (int i=0; i<EDGES; i++) e[i].f = 0;

	int FLOW = 0;
	while (bfs(N, SOURCE, SINK)) FLOW += dfs(SOURCE, SINK, SOURCE, INF);
	return FLOW;
}

#define MAXD 32
#define MAXT 400

int num[MAXD][MAXD][MAXT][2];
int di[5] = {0,1,-1,0,0};
int dj[5] = {0,0,0,1,-1};

int main() {
	int N, NUM, i, j, k, l, SOURCE, SINK, t=1, d[MAXD][MAXD], sx[MAXD*MAXD], sy[MAXD*MAXD], S, E;
	char m[MAXD][MAXD];
	
	while (cin >> N && N) {
		for (i=1; i<=N; i++) for (j=1; j<=N; j++) cin >> m[i][j];
		for (i=0; i<=N+1; i++) m[0][i] = m[i][0] = m[N+1][i] = m[i][N+1] = 'X';
		
		memset(d, -1, sizeof(d)); S = E = 0;
		for (i=1; i<=N; i++) { d[i][1] = 0; sx[E] = i; sy[E] = 1; E++; }
		while (S < E) {
			i = sx[S]; j = sy[S]; S++;
			for (k=1; k<5; k++) if (m[i+di[k]][j+dj[k]] == '.' && d[i+di[k]][j+dj[k]] == -1) {
				d[i+di[k]][j+dj[k]] = d[i][j]+1;
				sx[E] = i+di[k];
				sy[E] = j+dj[k];
				E++;
			}
		}
		S = MAXT; for (i=1; i<=N; i++) S = min(S, d[i][N]); E = S-- + N;
		
		NUM = 0;
		for (i=1; i<=N; i++) for (j=1; j<=N; j++) if (m[i][j] == '.') for (k=0; k<E; k++) for (l=0; l<2; l++) num[i][j][k][l] = NUM++;
		SOURCE = NUM++; SINK = NUM++;
		
		init(NUM);
		for (i=1; i<=N; i++) add_edge(SOURCE, num[i][1][0][0], 1, 0);
		for (i=1; i<=N; i++) for (j=1; j<=N; j++) if (m[i][j] == '.') for (k=0; k<E; k++) {
			add_edge(num[i][j][k][0], num[i][j][k][1], 1, 0);
			if (k<E-1) for (l=0; l<5; l++) if (m[i+di[l]][j+dj[l]] == '.') add_edge(num[i][j][k][1], num[i+di[l]][j+dj[l]][k+1][0], 1, 0);
		}
		
		while (E-S > 1) {
			int M = (S+E)/2;
			for (i=1; i<=N; i++) add_edge(num[i][N][M][1], SINK, 1, 0);
			if (dinic(NUM, SOURCE, SINK) == N) E = M;
			else S = M;
			for (i=1; i<=N; i++) n[num[i][N][M][1]].c.pop_back();
			n[SINK].c.clear();
			EDGES -= N;
		}
		cout << "Case " << t++ << ": " << E << endl;
	}

	return 0;
}
