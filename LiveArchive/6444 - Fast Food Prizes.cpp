#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 32
#define INF 128

int main() {
	int T, t, N, M, P[MAXN], p[MAXN][MAXN], v[MAXN], c[MAXN], i, j, RES, tmp;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> M;
		for (i=0; i<N; i++) {
			cin >> P[i];
			for (j=0; j<P[i]; j++) { cin >> p[i][j]; p[i][j]--;	}
			cin >> v[i];
		}
		for (i=0; i<M; i++) cin >> c[i];

		RES = 0;
		for (i=0; i<N; i++) {
			tmp = INF;
			for (j=0; j<P[i]; j++) tmp = min(tmp, c[p[i][j]]);
			RES += tmp*v[i];
		}
		cout << RES << endl;
	}

	return 0;
}
