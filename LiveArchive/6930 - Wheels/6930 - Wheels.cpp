#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1024
#define SQ(x) ( (x)*(x) )

struct node {
	int x, y, r, d;
	long long vn, vd;
	vector<int> adj;
} n[MAXN];

int gcd(int a, int b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int main() {
	int T, t, N, i, j, S, E, s[MAXN], cur, next, tmp;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=0; i<N; i++) {
			cin >> n[i].x >> n[i].y >> n[i].r;
			n[i].adj.clear(); n[i].d = 0;
		}
		n[0].d = n[0].vn = n[0].vd = 1;
		
		for (i=0; i<N; i++) for (j=i+1; j<N; j++) if (SQ(n[i].x-n[j].x)+SQ(n[i].y-n[j].y) == SQ(n[i].r+n[j].r)) {
			n[i].adj.push_back(j);
			n[j].adj.push_back(i);
		}
		
		S = E = 0; s[E++] = 0;
		while (S < E) {
			cur = s[S++];
			for (i=0; i<(int)n[cur].adj.size(); i++) {
				next = n[cur].adj[i];
				if (n[next].d == 0) {
					n[next].d = -n[cur].d;
					n[next].vn = n[cur].vn*n[cur].r;
					n[next].vd = n[cur].vd*n[next].r;
					tmp = gcd(n[next].vn, n[next].vd);
					n[next].vn /= tmp; n[next].vd /= tmp;
					s[E++] = next;
				}
			}
		}
		for (i=0; i<N; i++) {
			if (n[i].d == 0) cout << "not moving" << endl;
			else if (n[i].vd == 1) cout << n[i].vn << (n[i].d == 1 ? " clockwise" : " counterclockwise") << endl;
			else cout << n[i].vn << '/' << n[i].vd << (n[i].d == 1 ? " clockwise" : " counterclockwise") << endl;
		}
	}

	return 0;
}
