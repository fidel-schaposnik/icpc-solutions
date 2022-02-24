#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const double pi = 2.0*acos(0.0);

#define MAXN 16384
#define EPS 1E-9

struct hole {
	double x, y, z, r, volS;
} n[MAXN];

bool operator<(const hole &h1, const hole &h2) {
	return h1.z-h1.r < h2.z-h2.r;
}

int N;

double volS(double r) {
	return 4.0*pi*r*r*r/3.0;
}

double volB(double r, double z0) {
	return pi*(r*r*z0 - z0*z0*z0/3.0);
}

double vol(double z) {
	double RES = 100000.0*100000.0*z;
	for (int i=0; i<N; i++) {
		if (n[i].z-n[i].r < z) {
			if (n[i].z+n[i].r < z) RES -= n[i].volS;
			else if (n[i].z > z) RES -= n[i].volS/2.0 - volB(n[i].r, n[i].z-z);
			else RES -= n[i].volS/2.0 + volB(n[i].r, z-n[i].z);
		} else break;
	}
	return RES;
}

int main() {
	int S, i;
	double TOT, cur, l, r, m;
	
	while (cin >> N >> S) {
		TOT = 100000.0*100000.0*100000.0;
		for (i=0; i<N; i++) {
			cin >> n[i].r >> n[i].x >> n[i].y >> n[i].z;
			n[i].volS = volS(n[i].r);
			TOT -= n[i].volS;
		}
		sort(n,n+N);
		TOT /= S;
		
		cur = 0.0;
		for (i=0; i<S; i++) {
			l = 0.0; r = 100000.0-cur;
			while (r-l > EPS) {
				m = (l+r)/2.0;
				if (vol(cur+m)-vol(cur) > TOT) r = m;
				else l = m;
			}
			cur += (l+r)/2.0;
			printf("%.8lf\n", (l+r)/2.0/1000.0);
		}
	}
	
	return 0;
}
