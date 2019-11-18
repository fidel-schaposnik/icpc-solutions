#include <iostream>
using namespace std;

#define MAXN 32

int main() {
	int T, t, N, i, j, k, M[MAXN], m[MAXN][MAXN], RES, tmp;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=0; i<N; i++) {
			cin >> M[i];
			for (j=0; j<M[i]; j++) { cin >> m[i][j]; m[i][j]--; }
			m[i][M[i]++] = i;
		}
		
		RES = N;
		for (i=0; i<(1<<N); i++) {
			tmp = 0;
			for (j=0; j<N; j++) if ((i>>j)&1) tmp++;
			if (tmp > RES) continue;
			
			for (j=0; j<N; j++) {
				for (k=0; k<M[j]; k++) if ((i>>m[j][k])&1) break;
				if (k == M[j]) break;
			}
			if (j == N) RES = min(RES, tmp);
		}
		cout << RES << endl;
	}

	return 0;
}
