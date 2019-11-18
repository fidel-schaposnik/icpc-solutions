#include <iostream>
#include <vector>
using namespace std;

#define MAXN 65536
#define LOGMAXN 16

struct node {
	int p, d[2];
	vector< pair<int,int> > c;
} n[MAXN];

void process(int d[2], int v) {
	if (v > d[0]) { swap(d[0], d[1]); d[0] = v; }
	else if (v > d[1]) d[1] = v;
}

void fill(int cur, int p) {
	n[cur].p = p; n[cur].d[0] = n[cur].d[1] = 0;
	for (int i=0; i<(int)n[cur].c.size(); i++) {
		int next = n[cur].c[i].first;
		if (next == p) continue;
		
		fill(next, cur);
		process(n[cur].d, n[next].d[0]+n[cur].c[i].second);
	}
}

void fill2(int cur) {
	for (int i=0; i<(int)n[cur].c.size(); i++) {
		int next = n[cur].c[i].first;
		if (next == n[cur].p) continue;
		
		if (n[cur].d[0] == n[next].d[0]+n[cur].c[i].second) process(n[next].d, n[cur].d[1]+n[cur].c[i].second);
		else process(n[next].d, n[cur].d[0]+n[cur].c[i].second);
		fill2(next);
	}
}

int rmq_max[MAXN][LOGMAXN], rmq_min[MAXN][LOGMAXN];

int get_max(int s, int e) {
	int tmp = 31 - __builtin_clz(e-s);
	return max(rmq_max[s][tmp], rmq_max[e-(1<<tmp)][tmp]);
}

int get_min(int s, int e) {
	int tmp = 31 - __builtin_clz(e-s);
	return min(rmq_min[s][tmp], rmq_min[e-(1<<tmp)][tmp]);
}

bool check(int cant, int dif, int N) {
	for (int i=1; i+cant<=N+1; i++) if (get_max(i, i+cant)-get_min(i, i+cant) <= dif) return true;
	return false;
}

int main() {
	int N, M, i, j, a, b, w, Q, s, e, m;
	
	while (cin >> N >> M && (N!=0 || M!=0)) {
		for (i=1; i<=N; i++) n[i].c.clear();
		for (i=0; i<N-1; i++) {
			cin >> a >> b >> w;
			n[a].c.push_back(make_pair(b, w));
			n[b].c.push_back(make_pair(a, w));
		}
		
		fill(1, -1); fill2(1);
		for (i=1; i<=N; i++) rmq_max[i][0] = rmq_min[i][0] = n[i].d[0];
		for (j=1; (1<<j)<=N; j++) for (i=1; i+(1<<j)<=N+1; i++) {
			rmq_max[i][j] = max(rmq_max[i][j-1], rmq_max[i+(1<<(j-1))][j-1]);
			rmq_min[i][j] = min(rmq_min[i][j-1], rmq_min[i+(1<<(j-1))][j-1]);
		}
		
		for (i=0; i<M; i++) {
			cin >> Q;
			s = 1; e = N+1;
			while (e-s > 1) {
				m = (s+e)/2;
				if (check(m, Q, N)) s = m;
				else e = m;
			}
			cout << s << endl;
		}
	}

	return 0;
}
