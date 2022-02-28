#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

set< pair<double,double> > s;

int main() {
	int N, M, i, j;
	double W, U, V, T1, T2, L, P, dir, Ti, Tf, T, RES;
	char D;
	
	while (cin >> N >> W >> U >> V >> T1 >> T2) {
		s.clear();
		for (i=0; i<N; i++) {
			cin >> D >> M; dir = (D == 'E' ? 1.0 : -1.0);
			for (j=0; j<M; j++) {
				cin >> L >> P;
				Ti = -P/(dir*U) - W*(i+1)/V;
				Tf = -(P-dir*L)/(dir*U) - W*i/V;
				if (Ti < T2 && Tf > T1) s.insert(make_pair(max(Ti, T1), min(Tf, T2)));
			}
		}
		
		T = T1; RES = 0.0;
		for (set< pair<double, double> >::iterator it = s.begin(); it != s.end(); it++) {
			RES = max(RES, it->first - T);
			T = max(T, it->second);
		}
		RES = max(RES, T2-T);
		printf("%.6lf\n", RES);
	}

	return 0;
}
