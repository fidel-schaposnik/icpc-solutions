#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;

typedef vector<int> vi;

#define forn(i,n) for(int i = 0; i < (n); ++i)
#define forsn(i,m,n) for(int i = (m); i < (n); ++i)
#define si(a) (int)(a.size())
#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()

#define MAXN 128
typedef long double tipo;

int n,r,a[MAXN];
tipo dp[MAXN][MAXN], b, v, e, f;

tipo ff(int x) {
	if (x>=r) return 1.0/(v-e*(tipo)(x-r));
	else return 1.0/(v-f*(tipo)(r-x));	
}

tipo dist(int a, int b, int parada) {
	tipo res = 0.0;
	for(int i = a; i<b; ++i) {
		res+= ff(i-parada);	
	}		
	return res;
}

int main(){
	while (cin >> n && n) {
		forn(i,n) cin >> a[i+1];
		cin >> b >> r >> v >> e >> f;
		a[0] = 0;
		forn(i,n+1) dp[n][i] = 0.0;
		
		for(int i = n-1; i >= 0; --i) forn(j,i+1) {
			if (i==j) {
				dp[i][j] = dp[i+1][j] + dist(a[i],a[i+1],a[j]);	
			} else {
				dp[i][j] = min(dp[i+1][j] + dist(a[i],a[i+1],a[j]), dp[i+1][i] + dist(a[i],a[i+1],a[i]) + b);	
			}
		}
		printf("%.4lf\n", (double)dp[0][0]);
	}
	return 0;
}
