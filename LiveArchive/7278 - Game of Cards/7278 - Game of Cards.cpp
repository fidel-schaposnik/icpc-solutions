#include <iostream>
#include <algorithm>
using namespace std;

#define MAXK 16
#define MAXP 128
#define MAXN 1024

int main() {
	int P, p, K, N, i, j, n[MAXN], grundy[MAXP], v[MAXK], V, RES;
	
	while (cin >> P >> K) {
		RES = 0;
		for (p=0; p<P; p++) {
			cin >> N;
			for (i=0; i<N; i++) cin >> n[i];
			
			grundy[0] = 0;
			for (i=1; i<=N; i++) {
				V = 0;
				for (j=0; j<i && j<=K; j++) if (n[i-j-1] <= i-j) v[V++] = grundy[i-j-n[i-j-1]];
				sort(v, v+V);
				for (j=grundy[i]=0; j<V; j++) if (grundy[i] == v[j]) grundy[i]++;
			}
			RES ^= grundy[N];
		}
		
		if (!RES) cout << "Bob will win." << endl;
		else cout << "Alice can win." << endl;
	}

	return 0;
}
