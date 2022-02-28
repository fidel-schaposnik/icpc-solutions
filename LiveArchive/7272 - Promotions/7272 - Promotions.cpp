#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 8192

struct node {
	vector<int> c[2];
} n[MAXN];

bool v[MAXN];

int dfs(int cur, int dir) {
	v[cur] = true;
	int i, next, RES = 1;
	for (i=0; i<(int)n[cur].c[dir].size(); i++) {
		next = n[cur].c[dir][i];
		if (!v[next]) RES += dfs(next, dir);
	}
	return RES;
}

int main() {
	int A, B, N, E, i, j, a, b, RES;
	
	while (cin >> A >> B >> N >> E) {
		for (i=0; i<N; i++) for (j=0; j<2; j++) n[i].c[j].clear();
		for (i=0; i<E; i++) {
			cin >> a >> b;
			n[a].c[0].push_back(b);
			n[b].c[1].push_back(a);
		}
		
		RES = 0;
		for (i=0; i<N; i++) {
			memset(v, false, sizeof(v));
			if (dfs(i, 0) > N-A) RES++;
		}
		cout << RES << endl;
		
		RES = 0;
		for (i=0; i<N; i++) {
			memset(v, false, sizeof(v));
			if (dfs(i, 0) > N-B) RES++;
		}
		cout << RES << endl;
		
		RES = 0;
		for (i=0; i<N; i++) {
			memset(v, false, sizeof(v));
			if (dfs(i, 1) > B) RES++;
		}
		cout << RES << endl;
	}

	return 0;
}
