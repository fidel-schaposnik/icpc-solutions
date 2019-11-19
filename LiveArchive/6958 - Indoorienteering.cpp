#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 16
#define MAXM 1<<14
#define MAXV 1024

int N, LAST, V[MAXM];
long long L, n[MAXN][MAXN], v[MAXM][MAXV];

void dfs(int cant, int last, int mask, long long length) {
	if (cant == N/2 || cant == (N+1)/2) v[mask][V[mask]++] = length+n[last][LAST];
	
	if (cant < (N+1)/2) for (int i=1; i<N; i++) if (((mask>>i)&1) == 0) dfs(cant+1, i, mask^(1<<i), length+n[last][i]);
}

int main() {
	int i, j, mask, comp_mask;

	while (cin >> N >> L) {
		for (i=0; i<N; i++) for (j=0; j<N; j++) cin >> n[i][j];

		bool FLAG = false;
		for (LAST=1; !FLAG && LAST<N; LAST++) {
			memset(V, 0, sizeof(V));
			dfs(1, 0, 1^(1<<LAST), 0LL);
			for (mask=0; mask<(1<<N); mask++) sort(v[mask], v[mask]+V[mask]);
			for (mask=0; !FLAG && mask<(1<<N); mask++) {
				comp_mask = ((1<<N)-1)^mask^1^(1<<LAST);
				j = V[comp_mask]-1;
				for (i=0; !FLAG && i<V[mask]; i++) {
					while (j >= 0 && v[comp_mask][j]+v[mask][i] > L) j--;
					if (j>=0 && v[comp_mask][j]+v[mask][i] == L) FLAG = true;
				}
			}
		}

		if (FLAG) cout << "possible" << endl;
		else cout << "impossible" << endl;
	}

	return 0;
}
