#include <iostream>
using namespace std;

#define MAXP 1048576

void mul(long long a[2][2], long long b[2][2], long long c[2][2]) {
	for (int i=0; i<2; i++) for (int j=0; j<2; j++) {
		c[i][j] = 0LL;
		for (int k=0; k<2; k++) c[i][j] += a[i][k]*b[k][j];
	}
}

void modexp(long long a[2][2], int b, long long c[2][2], long long MOD) {
	long long tmp[2][2];
	
	for (int i=0; i<2; i++) for (int j=0; j<2; j++) c[i][j] = (i==j ? 1LL : 0LL);
	while (b) {
		if (b&1) {
			mul(a, c, tmp);
			for (int i=0; i<2; i++) for (int j=0; j<2; j++) c[i][j] = (tmp[i][j] > MOD ? MOD+tmp[i][j]%MOD : tmp[i][j]);
		}
		mul(a, a, tmp);
		for (int i=0; i<2; i++) for (int j=0; j<2; j++) a[i][j] = (tmp[i][j] > MOD ? MOD+tmp[i][j]%MOD : tmp[i][j]);
		b >>= 1;
	}
}

int p[MAXP];

int phi(int N) {
	int RES = 1;
	while (p[N]) {
		int prime = p[N], cur = 1;
		while (N%prime == 0) {
			cur *= prime;
			N /= prime;
		}
		RES *= cur - cur/prime;
	}
	if (N > 1) RES *= N-1;
	return RES;
}

long long modexp(long long x, int y, int MOD) {
	long long RES = 1LL;
	while (y) {
		if (y&1) RES = (RES*x)%MOD;
		x = (x*x)%MOD;
		y >>= 1;
	}
	return RES;
}

int main() {
	int T, t, P, N, i, j;
	long long M[2][2], RES[2][2], LEFT[2][2], RIGHT[2][2], A, B;
	
	for (i=4; i<MAXP; i+=2) p[i] = 2;
	for (i=3; i*i<MAXP; i+=2) if (!p[i]) for (j=i*i; j<MAXP; j+=2*i) p[j] = i;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> A >> B >> P >> N;

		M[0][0] = M[0][1] = M[1][0] = 1LL; M[1][1] = 0LL;
		modexp(M, N-1, RES, phi(P));

		cout << "Case #" << t << ": " << (modexp(B, RES[1][0], P)*modexp(A, RES[1][1], P))%P << endl;
	}

	return 0;
}
