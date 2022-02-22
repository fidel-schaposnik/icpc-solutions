#include <iostream>
#include <set>
#include <cmath>
using namespace std;

#define MAXN 32

int w[MAXN], CANT;
long long k[MAXN];
set<long long> s[2][4*MAXN];

void dfs(int pos, long long sum, int cant, int end, int id) {
	if (pos < end) {
		dfs(pos+1, sum, cant, end, id);
		dfs(pos+1, sum+k[pos]*w[pos], cant+w[pos], end, id);
	} else s[id][cant].insert(sum);
}

double get(long long G) {
	set<long long>::iterator it, it2;
	double RES = 1E15;
	
	for (int i=0; i<=CANT; i++) for (int j=0; j<=CANT; j++) if (i+j) {
		for (it=s[0][i].begin(); it!=s[0][i].end(); it++) {
			it2 = s[1][j].lower_bound(G*(i+j)-*it);
			if (it2 != s[1][j].end()) RES = min(RES, abs(G - (*it+*it2)/((double)(i+j))));
			if (it2 != s[1][j].begin()) {
				it2--;
				RES = min(RES, abs(G - (*it+*it2)/((double)(i+j))));
			}
		}
	}
	return RES;
}

int main() {
	int N, i, j;
	long long S, H;
	double dS, dH;
	
	while (cin >> N >> H >> S) {
		CANT = 0;
		for (i=0; i<N; i++) {
			cin >> k[i] >> w[i];
			CANT += w[i];
		}
		
		for (i=0; i<2; i++) for (j=0; j<=CANT; j++) s[i][j].clear();
		dfs(0, 0LL, 0, N/2, 0); dfs(N/2, 0LL, 0, N, 1);
		
		dH = get(H); dS = get(S);
		if (dH > dS) cout << "Swans" << endl;
		else if (dH < dS) cout << "Hawks" << endl;
		else cout << "Tie" << endl;
	}

	return 0;
}
