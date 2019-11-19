#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 64
#define MAXNODE 4*MAXN

int comp[MAXNODE], stack[MAXNODE], S, E;

struct node {
	vector<int> in, out;
} n[MAXNODE];

void dfs1(int cur) {
	comp[cur] = -1;
	for (int i=0; i<(int)n[cur].out.size(); i++) if (!comp[n[cur].out[i]]) dfs1(n[cur].out[i]);
	stack[E++] = cur;
}

void dfs2(int cur, int cur_comp) {
	comp[cur] = cur_comp;
	for (int i=0; i<(int)n[cur].in.size(); i++) if (comp[n[cur].in[i]] == -1) dfs2(n[cur].in[i], cur_comp);
}

int compfc(int N) {
	int RES = 0;
	
	memset(comp, 0, sizeof(comp)); S = E = 0;
	for (int i=0; i<N; i++) if (!comp[i]) dfs1(i);
	for (int i=N-1; i>=0; i--) if (comp[stack[i]] == -1) dfs2(stack[i], RES++);
	return RES;
}

void add_edge(int a, int b) {
	n[a].out.push_back(b);
	n[b].in.push_back(a);
}

void sii(int a, int b) {
	add_edge(a,b); add_edge(b,a);
}

int main() {
	int N, M, i, j, k, A, B, C, u, v, var[2][26][2], p[MAXN], cant[MAXN], RES;
	char s[MAXN][4];
	
	N = 0;
	for (i=0; i<2; i++) for (j=0; j<26; j++) for (k=0; k<2; k++) var[i][j][k] = N++;
	
	while (cin >> M) {
		for (i=0; i<M; i++) { cin >> s[i] >> p[i] >> cant[i]; p[i]--; }
		
		RES = 0;
		for (A=0; A<26; A++) for (B=0; B<A; B++) for (C=0; C<B; C++) {
			for (i=0; i<N; i++) { n[i].in.clear(); n[i].out.clear(); }
			
			add_edge(var[0][A][0], var[0][A][1]); add_edge(var[1][A][0], var[1][A][1]);
			add_edge(var[0][B][0], var[0][B][1]); add_edge(var[1][B][0], var[1][B][1]);
			add_edge(var[0][C][0], var[0][C][1]); add_edge(var[1][C][0], var[1][C][1]);
			
			for (i=0; i<26; i++) if (i != A && i != B && i != C) {
				sii(var[0][i][0], var[1][i][1]);
				sii(var[1][i][0], var[0][i][1]);
			}
			
			for (i=0; i<M; i++) {
				u = s[i][0]-'A'; v = s[i][1]-'A';
				if (cant[i] == 0) {
					add_edge(var[p[i]][u][0], var[p[i]][u][1]);
					add_edge(var[p[i]][v][0], var[p[i]][v][1]);
				} else if (cant[i] == 2) {
					add_edge(var[p[i]][u][1], var[p[i]][u][0]);
					add_edge(var[p[i]][v][1], var[p[i]][v][0]);
				} else {
					sii(var[p[i]][u][0], var[p[i]][v][1]);
					sii(var[p[i]][u][1], var[p[i]][v][0]);
				}
			}
			compfc(N);

			bool flag = true;
			for (i=0; i<2; i++) for (j=0; j<26; j++) if (comp[var[i][j][0]] == comp[var[i][j][1]]) flag = false;
			if (flag) RES++;
		}
		cout << RES << endl;
	}


	return 0;
}
