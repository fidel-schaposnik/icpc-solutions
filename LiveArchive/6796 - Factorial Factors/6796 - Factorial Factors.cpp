#include <iostream>
using namespace std;

#define MAXN 131072

int e[MAXN], p[MAXN];

int main() {
	int T, t, N, i, j, DIF, TOTAL;
	
	for (i=2; i*i<MAXN; i++) if (!p[i]) for (j=2*i; j<MAXN; j+=i) p[j] = i;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		
		for (i=2; i<=N; i++) e[i] = 1;
		for (i=N; i>=2; i--) if (p[i]) {
			e[p[i]] += e[i];
			e[i/p[i]] += e[i];
			e[i] = 0;
		}
		
		DIF = TOTAL = 0;
		for (i=2; i<=N; i++) {
			if (e[i]) { DIF++; TOTAL += e[i]; }
		}
		cout << DIF << ' ' << TOTAL << endl;
	}

	return 0;
}
