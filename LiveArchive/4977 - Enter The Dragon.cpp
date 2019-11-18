#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 1048576
#define INF 1000000000

#define LEFT(x) ( 2*(x) )
#define RIGHT(x) ( 2*(x)+1 )

int next[MAXN], m[MAXN], res[MAXN], rmq[2*MAXN];
bool state[MAXN];
vector<int> n[MAXN];

void init(int cur, int s, int e) {
	if (e-s == 1) rmq[cur] = INF;
	else {
		init(LEFT(cur), s, (s+e)/2);
		init(RIGHT(cur), (s+e)/2, e);
		rmq[cur] = min(rmq[LEFT(cur)], rmq[RIGHT(cur)]);
	}
}

void update(int cur, int s, int e, int p, int v) {
	if (e-s == 1) rmq[cur] = v;
	else {
		if (p < (s+e)/2) update(LEFT(cur), s, (s+e)/2, p, v);
		else update(RIGHT(cur), (s+e)/2, e, p, v);
		rmq[cur] = min(rmq[LEFT(cur)], rmq[RIGHT(cur)]);
	}
}

int main() {
	int T, t, N, M, i, tmp, CNT;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> M;
		
		init(1, 1, N+1);
		memset(next, 0, sizeof(next));
		memset(state, true, sizeof(state));
		for (i=1; i<=N; i++) n[i].clear();
		
		for (i=0; i<M; i++) {
			cin >> m[i];
			if (m[i]) n[m[i]].push_back(i);
		}

		for (i=1; i<=N; i++) if (!n[i].empty()) {
			update(1, 1, N+1, i, n[i][next[i]++]);
			n[i].push_back(INF);
		}
		
		bool FLAG = true; CNT = 0;
		memset(res, 0, sizeof(res));
		for (i=0; FLAG && i<M; i++) {
			if (m[i]) {
				if (!state[m[i]]) {
					update(1, 1, N+1, m[i], n[m[i]][next[m[i]]++]);
					state[m[i]] = true;
				} else FLAG = false;
			} else {
				CNT++;
				if (rmq[1] != INF) {
					res[i] = tmp = m[rmq[1]];
					update(1, 1, N+1, tmp, INF);
					state[tmp] = false;
				}
			}
		}
		
		if (!FLAG) cout << "NO" << endl;
		else {
			cout << "YES" << endl;
			for (i=0; i<M; i++) if (!m[i]) {
				cout << res[i];
				if (--CNT) cout << ' ';
				else cout << endl;
			}
		}
	}

	return 0;
}
