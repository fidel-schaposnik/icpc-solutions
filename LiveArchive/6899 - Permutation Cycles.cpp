#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1024

int main() {
	int T, t, N, n[MAXN], i, j, RES;
	bool v[MAXN];
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=1; i<=N; i++) cin >> n[i];
		
		memset(v, false, sizeof(v)); RES = 0;
		for (i=1; i<=N; i++) if (!v[i]) {
			j = i; RES++;
			while (!v[j]) {
				v[j] = true;
				j = n[j];
			}
		}
		cout << RES << endl;
	}

	return 0;
}
