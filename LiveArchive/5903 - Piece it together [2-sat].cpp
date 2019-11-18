#include <iostream>
#include <vector>
#include <map>
using namespace std;

/* 2-SAT */

#define MAXD 512
#define MAXN 1048576

struct node {
   int id, up;
   vector<int> c;
} n[MAXN];

int stack[MAXN], STACK, ID, COMP;

void scc_dfs(int cur, int comp[]) {
   n[cur].id = n[cur].up = ID++;
   stack[STACK++] = cur;

   for (int i=0; i<(int)n[cur].c.size(); i++) {
      if (n[n[cur].c[i]].id == -1) {
         scc_dfs(n[cur].c[i], comp);
         n[cur].up = min(n[cur].up, n[n[cur].c[i]].up);
      } else if (comp[n[cur].c[i]] == -1) {
         n[cur].up = min(n[cur].up, n[n[cur].c[i]].id);
      }
   }

   if (n[cur].up == n[cur].id) {
      while (stack[STACK-1] != cur) {
         comp[stack[STACK-1]] = COMP;
         STACK--;
      }
      comp[cur] = COMP++;
      STACK--;
   }
}

void scc(int comp[], int NODES) {
   for (int i=0; i<NODES; i++) comp[i] = n[i].id = n[i].up = -1;

   STACK = ID = COMP = 0;
   for (int i=0; i<NODES; i++) if (n[i].id == -1) scc_dfs(i, comp);
}

map< pair< pair<int,int>, pair<int,int> >, int > id[2];
char m[MAXD][MAXD];

int CANT, c[MAXN];
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int get(int i1, int j1, int i2, int j2, int neg) {
	pair<int, int> a = make_pair(i1,j1), b = make_pair(i2,j2);
	pair< pair<int, int>, pair<int, int> > tmp = make_pair(min(a,b), max(a,b));
	if (id[0].find(tmp) == id[0].end()) {
		id[0][tmp] = CANT; n[CANT++].c.clear();
		id[1][tmp] = CANT; n[CANT++].c.clear();
	}
	return id[neg][tmp];
}

void add_edge(int a, int b) { n[a].c.push_back(b); }

int main() {
	int T, t, N, M, i, j, k, l, B, W;
	bool FLAG;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> M; B = W = 0;
		for (i=1; i<=N; i++) for (j=1; j<=M; j++) {
			cin >> m[i][j];
			if (m[i][j] == 'B') B++;
			else if (m[i][j] == 'W') W++;
		}
		for (i=0; i<=N+1; i++) m[i][0] = m[i][M+1] = '.';
		for (j=0; j<=M+1; j++) m[0][j] = m[N+1][j] = '.';
		
		if (2*B == W) {
			id[0].clear(); id[1].clear(); CANT = 0; FLAG = true;
			for (i=1; i<=N; i++) for (j=1; j<=M; j++) {
				if (m[i][j] == 'B') {
					if (m[i+1][j] != 'W' && m[i-1][j] != 'W') FLAG = false;
					else if (m[i+1][j] != 'W') add_edge(get(i, j, i-1, j, 1), get(i, j, i-1, j, 0));
					else if (m[i-1][j] != 'W') add_edge(get(i, j, i+1, j, 1), get(i, j, i+1, j, 0));
					else {
						add_edge(get(i, j, i-1, j, 1), get(i, j, i+1, j, 0));
						add_edge(get(i, j, i+1, j, 1), get(i, j, i-1, j, 0));
						add_edge(get(i, j, i-1, j, 0), get(i, j, i+1, j, 1));
						add_edge(get(i, j, i+1, j, 0), get(i, j, i-1, j, 1));
					}
					
					if (m[i][j+1] != 'W' && m[i][j-1] != 'W') FLAG = false;
					else if (m[i][j+1] != 'W') add_edge(get(i, j, i, j-1, 1), get(i, j, i, j-1, 0));
					else if (m[i][j-1] != 'W') add_edge(get(i, j, i, j+1, 1), get(i, j, i, j+1, 0));
					else {
						 add_edge(get(i, j, i, j-1, 1), get(i, j, i, j+1, 0));
						 add_edge(get(i, j, i, j+1, 1), get(i, j, i, j-1, 0));
						 add_edge(get(i, j, i, j-1, 0), get(i, j, i, j+1, 1));
						 add_edge(get(i, j, i, j+1, 0), get(i, j, i, j-1, 1));
					}
				} else if (m[i][j] == 'W') {
					for (k=0; k<4; k++) for (l=k+1; l<4; l++) if (m[i+dx[k]][j+dy[k]] == 'B' && m[i+dx[l]][j+dy[l]] == 'B') {
						add_edge(get(i, j, i+dx[k], j+dy[k], 0), get(i, j, i+dx[l], j+dy[l], 1));
						add_edge(get(i, j, i+dx[l], j+dy[l], 0), get(i, j, i+dx[k], j+dy[k], 1));
					}
				}
			}
			scc(c, CANT);
			for (i=0; i<CANT; i+=2) if (c[i] == c[i+1]) FLAG = false;

			if (FLAG) cout << "YES" << endl;
			else cout << "NO" << endl;
		} else cout << "NO" << endl;
	}

	return 0;
}
