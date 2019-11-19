#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int N, M, i, j, c[64];
	
	bool flag = false;
	while (cin >> N >> M) {
		if (flag) cout << endl;
		else flag = true;
		
		memset(c, 0, sizeof(c));
		for (i=1; i<=N; i++) for (j=1; j<=M; j++) c[i+j]++;
		for (i=j=0; i<=N+M; i++) j = max(j, c[i]);
		for (i=0; i<=N+M; i++) if (c[i] == j) cout << i << endl;
	}

	return 0;
}
