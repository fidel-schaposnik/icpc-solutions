#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAXN 16

int N, val[26], L, COUNT;
string n[MAXN];
char l[MAXN];
bool first[26];
long long mul[26];

void dfs(int cur, int curm, long long RES) {
	if (cur == L) {
		if (!RES) COUNT++;
	} else {
		for (int i=0; i<10; i++) if (((curm>>i)&1) == 0 && (i || !first[l[cur]-'A'])) dfs(cur+1, curm^(1<<i), RES+mul[l[cur]-'A']*i);
	}
}

int main() {
	int i, j;
	bool v[26];
	long long pow10[MAXN];
	
	pow10[0] = 1LL;
	for (i=1; i<MAXN; i++) pow10[i] = pow10[i-1]*10LL;
	
	while (cin >> N) {
		L = 0;
		memset(v, false, sizeof(v));
		memset(first, false, sizeof(first));
		memset(mul, 0LL, sizeof(mul));
		for (i=0; i<N; i++) {
			cin >> n[i]; first[n[i][0]-'A'] = true;
			for (j=0; j<(int)n[i].size(); j++) {
				if (!v[n[i][j]-'A']) {
					l[L++] = n[i][j];
					v[n[i][j]-'A'] = true;
				}
				mul[n[i][j]-'A'] += (i<N-1 ? 1LL : -1LL)*pow10[n[i].size()-1-j];
			}
		}
		
		COUNT = 0;
		dfs(0, 0, 0LL);
		cout << COUNT << endl;
	}

	return 0;
}
