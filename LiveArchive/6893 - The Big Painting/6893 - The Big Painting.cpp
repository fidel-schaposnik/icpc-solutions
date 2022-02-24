#include <iostream>
using namespace std;

#define MAXN 2048
#define VALUE(x) ( (x)=='o' ? 3ULL : 7ULL )

typedef unsigned long long HASH;

HASH h[MAXN][MAXN], pow33[MAXN], pow41[MAXN];

HASH calc(int a, int b, int c, int d) {
	return h[b][d] - h[a][d]*pow41[b-a] - h[b][c]*pow33[d-c] + h[a][c]*pow33[d-c]*pow41[b-a];
}

int main() {
	int Rp, Cp, R, C, i, j, RES;
	HASH tmp, PATTERN;
	char tmpc;
	
	pow33[0] = pow41[0] = 1ULL;
	for (i=1; i<MAXN; i++) { pow33[i] = pow33[i-1]*33ULL; pow41[i] = pow41[i-1]*41ULL; }
	
	while (cin >> Rp >> Cp >> R >> C) {
		
		PATTERN = 0;
		for (i=0; i<Rp; i++) {
			tmp = 0ULL;
			for (j=0; j<Cp; j++) {
				cin >> tmpc;
				tmp = tmp*33ULL + VALUE(tmpc);
			}
			PATTERN = PATTERN*41ULL + tmp;
		}
		
		for (i=0; i<R; i++) {
			h[i+1][0] = 0ULL;
			for (j=0; j<C; j++) {
				cin >> tmpc;
				h[i+1][j+1] = h[i+1][j]*33ULL + VALUE(tmpc);
			}
		}
		for (i=1; i<=R; i++) for (j=1; j<=C; j++) h[i][j] += h[i-1][j]*41ULL;
		
		RES = 0;
		for (i=0; i+Rp<=R; i++) for (j=0; j+Cp<=C; j++) if (calc(i,i+Rp,j,j+Cp) == PATTERN) RES++;
		cout << RES << endl;
	}

	return 0;
}
