#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAXN 1024
#define EPS 1E-12

double n[MAXN], m[MAXN];

int main() {
	int N, M, i;
	double W;
	bool flag;
	
	while (cin >> N >> M >> W && N && M && abs(W) > EPS) {
		W /= 2.0;
		for (i=0; i<N; i++) cin >> n[i];
		for (i=0; i<M; i++) cin >> m[i];
		
		sort(n,n+N); sort(m,m+M);
		flag = (n[0]-W < EPS) && (n[N-1]+W > 75.0-EPS) && (m[0]-W < EPS) && (m[M-1]+W > 100.0-EPS);
		for (i=1; flag && i<N; i++) if (n[i-1]+W < n[i]-W-EPS) flag = false;
		for (i=1; flag && i<N; i++) if (m[i-1]+W < m[i]-W-EPS) flag = false;
		if (flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}
