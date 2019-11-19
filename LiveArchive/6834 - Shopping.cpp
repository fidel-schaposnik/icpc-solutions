#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 1024

bool v[MAXN];

int main() {
	int N, M, i, j, RES, c, d;
	
	while (cin >> N >> M) {	
		memset(v, false, sizeof(v));
		for (i=0; i<M; i++) {
			cin >> c >> d;
			for (j=c; j<d; j++) v[j] = true;
		}
		
		RES = N+1;
		for (i=0; i<N; i++) {
			if (v[i]) RES += 2;
		}
		cout << RES << endl;
	}

	return 0;
}
