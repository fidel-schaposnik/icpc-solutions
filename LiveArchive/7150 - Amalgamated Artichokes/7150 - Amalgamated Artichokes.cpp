#include <iostream>
#include <cmath>
using namespace std;

int main() {
	int P, A, B, C, D, N, i;
	double tmp, MAX, RES;
	
	while (cin >> P >> A >> B >> C >> D >> N) {
		MAX = -1000000.0; RES = 0.0;
		for (i=1; i<=N; i++) {
			tmp = P*(sin(A*i+B) + cos(C*i+D) + 2.0);
			RES = max(RES, MAX-tmp);
			MAX = max(MAX, tmp);
		}
		printf("%.8lf\n", RES);
	}

	return 0;
}
