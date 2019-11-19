#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define INF 1000000000
#define MAXN 16384
#define MAXE 262144

struct node {
	int d, di;
	vector<int> c, w;
} n[MAXN];

struct edge {
	int a, b, d;
} e[MAXE];

set< pair<int, int> > s;

void dijkstra(int START, int N) {
	int i, cur, next;
	
	s.clear(); s.insert(make_pair(0, START));
	for (i=0; i<N; i++) n[i].d = INF; n[START].d = 0;
	while (!s.empty()) {
		cur = s.begin()->second;
		s.erase(s.begin());
		for (i=0; i<(int)n[cur].c.size(); i++) {
			next = n[cur].c[i];
			if (n[cur].d + n[cur].w[i] < n[next].d) {
				if (n[next].d < INF) s.erase(make_pair(n[next].d, next));
				n[next].d = n[cur].d + n[cur].w[i];
				s.insert(make_pair(n[next].d, next));
			}
		}
	}
}

int main() {
	int N, E, i, RES;
	
	while (cin >> N >> E) {
		for (i=0; i<N; i++) {
			n[i].c.clear();
			n[i].w.clear();
		}
		
		for (i=0; i<E; i++) {
			cin >> e[i].a >> e[i].b >> e[i].d;
			n[e[i].a].c.push_back(e[i].b);
			n[e[i].a].w.push_back(e[i].d);
			
			n[e[i].b].c.push_back(e[i].a);
			n[e[i].b].w.push_back(e[i].d);
		}
		
		dijkstra(0, N);
		for (i=0; i<N; i++) n[i].di = n[i].d;
		dijkstra(N-1, N);
		
		RES = 0;
		for (i=0; i<E; i++) if (n[e[i].a].di + e[i].d + n[e[i].b].d == n[N-1].di || n[e[i].a].d + e[i].d + n[e[i].b].di == n[N-1].di) RES += e[i].d;
		cout << 2*RES << endl;
	}

	return 0;
}
