#include <iostream>
#include <set>
using namespace std;

int b[5][4] = {
{1,2,3,-1},
{4,5,6,-1},
{7,8,9,-1},
{-1,0,-1,-1},
{-1,-1,-1,-1}
};

set<int> n;

void dfs(int x, int y, int cur) {
	n.insert(cur);

	if (b[x][y] != -1 && cur < 1000) {
		if (cur || b[x][y]) dfs(x, y, cur*10+b[x][y]);
		dfs(x+1, y, cur);
		dfs(x, y+1, cur);
	}
}

int main() {
	int i, j, t, T, N;
	set<int>::iterator it1, it2;
	
	for (i=0; i<3; i++) for (j=0; j<3; j++) dfs(i,j,0);
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		it1 = it2 = n.lower_bound(N); it2--;
		if (N-*it2 < *it1-N) cout << *it2 << endl;
		else cout << *it1 << endl;
	}

	return 0;
}
