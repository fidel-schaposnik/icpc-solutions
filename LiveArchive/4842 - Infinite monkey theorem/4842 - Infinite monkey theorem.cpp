#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

#define MAXS 16
#define MAXM 1024

double p[MAXS][MAXM];

int main() {
	int N, M, i, j, k, S, next[MAXS][26];
	double prob[26], RES;
	char tmpc;
	string s, tmp;
	
	while (cin >> N >> M && (N!=0 || M!=0)) {
		for (i=0; i<26; i++) prob[i] = 0.0;
		for (i=0; i<N; i++) {
			cin >> tmpc;
			cin >> prob[tmpc-'a'];
		}
		cin >> s; S = (int)s.size();
		
		for (i=0; i<S; i++) for (tmpc='a'; tmpc<='z'; tmpc++) {
			tmp = s.substr(0,i)+tmpc;
			for (j=i+1; j>=0; j--) if (s.substr(0,j) == tmp.substr(tmp.size()-j,j)) break;
			next[i][tmpc-'a'] = j;
		}

		for (i=0; i<MAXS; i++) for (j=0; j<MAXM; j++) p[i][j] = 0.0; p[0][0] = 1.0;
		for (i=0; i<M; i++) for (j=0; j<S; j++) for (k=0; k<26; k++) p[next[j][k]][i+1] += p[j][i]*prob[k];
		
		RES = 0.0;
		for (i=0; i<S; i++) RES += p[i][M];
		printf("%.2lf%\n", 100.0*(1.0-RES));
	}

	return 0;
}
