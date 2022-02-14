#include <iostream>
#include <map>
using namespace std;

#define MAXT 2097152
#define MAXN 32
#define MOD 9999991LL
#define LEFT(x) ( 2*(x) )
#define RIGHT(x) ( 2*(x)+1 )

map<int,int> tree, cant;
long long comb[MAXN][MAXN];

void insert(int cur, int val) {
	if (!tree[cur]) tree[cur] = val;
	else if (tree[cur] > val) insert(LEFT(cur), val);
	else insert(RIGHT(cur), val);
}

long long calc(int cur) {
	if (!tree[cur]) { cant[cur] = 0; return 1LL; }
	else {
		int l=LEFT(cur), r=RIGHT(cur);
		long long RES = calc(l)*calc(r)%MOD;
		cant[cur] = cant[l]+cant[r]+1;
		return RES*comb[cant[cur]-1][cant[l]]%MOD;
	}
}

int main() {
	int T, t, N, i, j, tmp;
	
	comb[0][0] = comb[1][0] = comb[1][1] = 1LL;
	for (i=2; i<MAXN; i++) {
		comb[i][0] = comb[i][i] = 1LL;
		for (j=1; j<i; j++) comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
	}
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		
		tree.clear(); cant.clear();
		for (i=0; i<N; i++) {
			cin >> tmp;
			insert(1, tmp);
		}
		cout << calc(1) << endl;
	}

	return 0;
}
