#include <iostream>
#include <string>
#include <map>
using namespace std;

#define MAXN 1048576

map<string, int> v;
string s[MAXN];

int solve(string cur) {
	if (v.find(cur) == v.end()) {
		v[cur] = 0;
		for (int i=0; i<(int)cur.size(); i++) if (i == 0 || cur[i] != cur[i-1]) {
			int j;
			for (j=i+1; j<(int)cur.size() && cur[j]==cur[i]; j++);
			if (j-i > 1 && solve(cur.substr(0,i)+cur.substr(j,cur.size()-j)) == 1) { v[cur] = 1; break; }
		}
	}
	return v[cur];
}

int main() {
	int T, t, i;
	string tmp;
	
	v[""] = 1;
	
	cin >> T;
	for (i=0; i<T; i++) {
		cin >> tmp;
		cout << solve(tmp) << endl;
	}

	return 0;
}
