#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 256

int N, c[MAXN][MAXN];
string i2s[MAXN];
map<string, int> s2i;
bool v[MAXN];
set<string> ans;

int id(string name) {
	if (s2i.find(name) == s2i.end()) { s2i[name] = N; i2s[N] = name; N++; }
	return s2i[name];
}

void dfs(int cur) {
	v[cur] = true;
	for (int i=0; i<N; i++) if (c[cur][i] && !v[i]) dfs(i);
}

int main() {
	int M, i, j, t = 1;
	string a, b;
	
	while (cin >> M && M) {
		N = 0; s2i.clear();
		memset(c, 0, sizeof(c));
		for (i=0; i<M; i++) {
			cin >> a >> b;
			c[id(a)][id(b)] = 1;
		}
		
		ans.clear();
		for (i=0; i<N; i++) for (j=0; j<N; j++) if (c[i][j]) {
			memset(v, false, sizeof(v));
			c[i][j] = 0;
			dfs(i);
			if (v[j]) ans.insert(i2s[i]+","+i2s[j]);
			else c[i][j] = 1;
		}
		
		cout << "Case " << t++ << ": " << ans.size();
		for (set<string>::iterator it=ans.begin(); it!=ans.end(); it++) cout << ' ' << *it;
		cout << endl;
	}

	return 0;
}
