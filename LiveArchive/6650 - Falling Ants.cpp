#include <iostream>
using namespace std;

int main() {
	int N, i, j, v[128], d[128], MAXD, MAXV;
	
	while (cin >> N && N!=0) {
		MAXD = MAXV = 0;
		for (i=0; i<N; i++) {
			v[i] = 1;
			for (j=0; j<3; j++) { cin >> d[i]; v[i] *= d[i]; }
			if (MAXD < d[i]) { MAXD = d[i]; MAXV = v[i]; }
			else if (MAXD == d[i]) MAXV = max(MAXV, v[i]);
		}
		cout << MAXV << endl;
	}

	return 0;
}
