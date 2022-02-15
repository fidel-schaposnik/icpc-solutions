#include <iostream>
using namespace std;

#define MAXN 5000001

int p[MAXN], phi[MAXN];

int fact(int n, int f[]) {
	int F = 0;
	while (p[n]) {
		f[F++] = p[n];
		n /= p[n];
	}
	f[F++] = n;
	return F;
}

unsigned long long tmp, RES[MAXN];

void div(int cur, int f[], int s, int e) {
    if (s == e) tmp += ((unsigned long long)phi[cur])*cur/2ULL;
    else {
        int m;
        for (m=s+1; m<e && f[m]==f[s]; m++);
        for (int i=s; i<=m; i++) {
            div(cur, f, m, e);
            cur *= f[s];
        }
    }
}

int main() {
	int i, j, F, f[32], N, T, t;
	
	for (i=4; i<MAXN; i+=2) p[i] = 2;
	for (i=3; i*i<MAXN; i+=2) if (!p[i]) for (j=i*i; j<MAXN; j+=2*i) if (!p[j]) p[j] = i;
	
	phi[1] = 1;
	for (i=2; i<MAXN; i++) {
		if (!p[i]) phi[i] = i-1;
		else {
			j = i; phi[i] = 1;
			while (j%p[i] == 0) {
				j /= p[i];
				phi[i] *= p[i];
			}
			phi[i] = (phi[i] - phi[i]/p[i])*phi[j];
		}
	}
	
	for (i=2; i<MAXN; i++) {
		F = fact(i, f);
		tmp = 0LL; div(1, f, 0, F);
		RES[i] = i*tmp;
	}
	for (i=2; i<MAXN; i++) RES[i] += RES[i-1];
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N;
		cout << "Case " << t << ": " << RES[N] << endl;
	}
	
	return 0;
}
