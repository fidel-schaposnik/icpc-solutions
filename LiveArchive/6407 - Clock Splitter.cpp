#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#define MAXN 131072
#define INF 1000000000000000000LL

long long n[2*MAXN], v[MAXN];

int main() {
	int N, i, s, e, m, BEST;
	long long TOT, BESTDIF, tmp;
	
	while (cin >> N && N) {
		n[0] = 0LL;
		for (i=1; i<=N; i++) n[i] = n[i+N] = i;
		for (i=1; i<=2*N; i++) n[i] += n[i-1];
		TOT = ((long long)N)*((long long)(N+1LL))/2LL;
		
		BEST = 0; BESTDIF = INF;
		for (i=1; i<=N; i++) {
			s = i; e = 2*N+1;
			while (e-s > 1) {
				m = (s+e)/2;
				if (2LL*(n[m]-n[i-1]) < TOT) s = m;
				else e = m;
			}
			if (abs(TOT-2LL*(n[s]-n[i-1])) < abs(TOT-2LL*(n[e]-n[i-1]))) v[i] = s;
			else v[i] = e;
			
			
			if (abs(TOT-2LL*(n[v[i]]-n[i-1])) < BESTDIF) { BEST = i; BESTDIF = abs(TOT-2LL*(n[v[i]]-n[i-1])); }
		}
		cout << BEST << ' ' << v[BEST] << endl;
	}

	return 0;
}
