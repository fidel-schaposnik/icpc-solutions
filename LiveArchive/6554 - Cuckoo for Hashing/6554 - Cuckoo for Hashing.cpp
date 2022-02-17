#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1024

int n[2][MAXN], N[2];

void insert(int val, int cur) {
	int tmp = val%N[cur], old = n[cur][tmp];
	
	n[cur][tmp] = val;
	if (old != -1) insert(old, 1-cur);
}

int main() {
	int M, i, j, tmp, t=1;
	
	while (cin >> N[0] >> N[1] >> M && (N[0]!=0 || N[1]!=0 || M!=0)) {
		
		memset(n, -1, sizeof(n));
		for (i=0; i<M; i++) {
			cin >> tmp;
			insert(tmp, 0);
		}
		
		cout << "Case " << t++ << ":" << endl;
		for (i=0; i<2; i++) {
			tmp = 0;
			for (j=0; j<N[i]; j++) if (n[i][j] != -1) tmp++;
			if (tmp) {
				cout << "Table " << i+1 << endl;
				for (j=0; j<N[i]; j++) if (n[i][j] != -1) cout << j << ":" << n[i][j] << endl;
			}
		}
	}

	return 0;
}
