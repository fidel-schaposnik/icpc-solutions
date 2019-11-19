#include <cstdio>
#include <iostream>
#include <complex>
using namespace std;

/* FFT */

#define MAXN 524288

typedef complex<long double> cpx;
const double dos_pi = 4.0*acos(0.0);

cpx n[MAXN], m[MAXN], angle[2][MAXN];

void fft(cpx x[], cpx y[], int dx, int N, int dir) {
	if (N > 1) {
		fft(x, y, 2*dx, N/2, dir);
		fft(x+dx, y+N/2, 2*dx, N/2, dir);
		for (int i=0; i<N/2; i++) {
			cpx even = y[i], odd = angle[dir][i*dx]*y[i+N/2];
			y[i] = even+odd;
			y[i+N/2] = even-odd;
		}
	} else y[0] = x[0];
}

int main() {
	int N, M, i, tmp, RES;
	
	for (i=0; i<MAXN; i++) {
		angle[0][i] = exp(cpx(0,dos_pi*i/MAXN));
		angle[1][i] = conj(angle[0][i]);
	}
	
	while (scanf("%d", &N) != EOF) {
		for (i=0; i<MAXN; i++) n[i] = cpx(0,0);
		
		n[0] = cpx(1, 0);
		for (i=1; i<=N; i++) {
			scanf("%d", &tmp);
			n[tmp] = cpx(1,0);
		}
		
		fft(n,m,1,MAXN,0);
		for (i=0; i<MAXN; i++) m[i] *= m[i];
		fft(m,n,1,MAXN,1);
		
		scanf("%d", &M); RES = 0;
		for (i=0; i<M; i++) {
			scanf("%d", &tmp);
			if (real(n[tmp]) > 0.5) RES++;
		}
		printf("%d\n", RES);
	}

	return 0;
}
