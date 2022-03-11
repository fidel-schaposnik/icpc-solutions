#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define forn(i,n) for(int i = 0; i < (n); i++)
#define forsn(i,m,n) for(int i = (m); i < (n); i++)
#define dforn(i,n) for(int i = (n-1); i >=0; i--)

typedef double tint;

#define MAXN 50100
#define OO 1000000000.0
#define eps 1E-10

int N;
tint x[MAXN], y[MAXN];
tint xf;

bool check(tint R){
	tint m = -OO, M = OO;
	
	forn(i,N){
		if(R<y[i]) return false;
		tint ea = sqrt(R*R - y[i]*y[i]);
		m = max(m, x[i] - ea);
		M = min(M, x[i] + ea);
	}	
	if(m<=M){ xf = (m+M)/2.0; return true; }
	else return false;
}

int main(){
	tint m, M;
	
	while(true){
		scanf("%d", &N);
		if (!N) break;
		
		m = 0; M = OO;
		forn(i, N) { scanf("%lf %lf", &x[i], &y[i]); if(y[i]<0.0) y[i] = -y[i]; }

		while(M-m > eps){
			tint mid = (m+M)/2.0;
			if(check(mid) == true) M = mid;
			else m = mid;	
		}
		
		printf("%.9lf %.9lf\n", xf, (M+m)/2.0);
	}
	
	return 0;
}
