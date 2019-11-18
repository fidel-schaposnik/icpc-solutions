#include <iostream>
#include <vector>
using namespace std;

/* Dinic - FLOW */

#define MAXN 512
#define MAXE 65536
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


int main() {
    int N, M, a[128], b[128], i, j, tmp, SOURCE, SINK, source, sink, S, E, MID, total, t, T;

    cin >> T;
    for (t=1; t<=T; t++) {
        cin >> N >> M;

        init(2*N+4);
        SOURCE = 2*N; SINK = 2*N+1; source = 2*N+2; sink = 2*N+3;
    
        total = 0;
        for (i=0; i<N; i++) {
            cin >> a[i] >> b[i] >> tmp;
            j = tmp/M; if (tmp%M) j++;
            add_edge(SOURCE, i, j, 0);
            add_edge(i, source, INF, 0);
            add_edge(sink, N+i, INF, 0);
            add_edge(N+i, SINK, j, 0);
            total += j;
        }
    
        for (i=0; i<N; i++) for (j=0; j<N; j++) {
            cin >> tmp;
            if (b[i]+tmp < a[j]) add_edge(j, N+i, INF, 0);
        }

        S = 0; E = total;
        while (E-S > 1) {
            MID = (S+E)/2;
            add_edge(source, sink, MID, 0);
            if (dinic(2*N+4, SOURCE, SINK) == total) E = MID;
            else S =  MID;
            EDGES--;
        }
        cout << "Case " << t << ": " << E << endl;
    }

    return 0;
}
