#include <iostream>
#include <set>
using namespace std;

#define MAXP 65536
#define MAXF 32
#define INF 1000000000000000000LL

int p[MAXP], P, X, Y, A;
long long BEST;

long long modexp(long long a, int k, long long mod) {
	long long RES = 1LL;
	while (k) {
		if (k&1) RES = (RES*a)%mod;
		k >>= 1;
		a = (a*a)%mod;
	}
	return RES;
}

void dfs(int pos, int cur, int *f, int F) {
	if (pos < F) {
		int i, j;
		for (j=pos+1; j<F && f[j]==f[pos]; j++);
		
		dfs(j, cur, f, F);
		for (i=pos; i<j; i++) dfs(j, cur = cur*f[i], f, F);
	} else {
		long long mod = X*Y;
		if ((((long long)A)*modexp(2LL, cur, mod))%mod == ((long long)A)%mod) BEST = min(BEST, (long long)cur);
	}
}

int main() {
	int T, t, i, j, tmp, F, f[MAXF], phi;
	
	for (i=2; i*i<MAXP; i++) if (!p[i]) for (j=2*i; j<MAXP; j+=i) p[j] = i;
	
	P = 0;
	for (i=2; i<MAXP; i++) if (!p[i]) p[P++] = i;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> X >> Y >> A;
		
		tmp = X*Y; phi = 1;
		for (i=0; i<P; i++) if (tmp%p[i] == 0) {
			phi *= p[i]-1; tmp /= p[i];
			while (tmp%p[i] == 0) {
				phi *= p[i];
				tmp /= p[i];
			}
		}
		
		F = 0;
		for (i=0; i<P; i++) while (phi%p[i] == 0) {
			f[F++] = p[i];
			phi /= p[i];
		}
		
		BEST = INF;
		dfs(0, 1, f, F);
		
		if (BEST < INF) cout << BEST << endl;
		else cout << "IMPOSSIBLE!" << endl;
	}

	return 0;
}
