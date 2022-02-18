#include <iostream>
#include <cstring>
using namespace std;

#define MAXL 64

unsigned long long L[MAXL];

string tostring(unsigned long long mask, int l) {
	string RES = "";
	for (int i=0; i<l; i++) {
		if ((mask>>i)&1) RES = 'b'+RES;
		else RES = 'a'+RES;
	}
	return RES;
}

unsigned long long count[MAXL];
bool valid[MAXL], calc_valid[MAXL], calc_count[MAXL];

bool _valid(const string &s, int l) {
	if (!calc_valid[l]) {
		valid[l] = (l == 0 || (s[l-1] == 'a' && _valid(s, l-1)) || (l >= 2 && s[l-1] == 'b' && _valid(s, l-2)));
		calc_valid[l] = true;
	}
	return valid[l];
}

unsigned long long _count(const string &s, int l) {
	if (!calc_count[l]) {
		if (l >= 1) {
			count[l] += _count(s, l-1);
			if (s[l-1] == 'b' && _valid(s, l-1)) count[l]++;
		}
		if (l >= 2) {
			count[l] += 2ULL*_count(s, l-2);
			if (s[l-2] == 'b' && _valid(s, l-2)) count[l]++;
		}
		calc_count[l] = true;
	}
	return count[l];
}

string find(unsigned long long k, int l) {
	unsigned long long S = 0, E = 1ULL<<l, M;
	while (E-S > 1ULL) {
		M = (S+E)/2ULL;
		memset(calc_valid, false, sizeof(calc_valid));
		memset(calc_count, false, sizeof(calc_count));
		memset(count, 0ULL, sizeof(count));
		if (_count(tostring(M, l), l) <= k) S = M;
		else E = M;
	}
	return tostring(S, l);
}

int main() {
	int i, t = 1;
	unsigned long long N, M, tmp;
	
	L[0] = L[1] = 1;
	for (i=2; i<MAXL; i++) L[i] = L[i-1]+2ULL*L[i-2];
	
	while (cin >> N >> M && (N!=0 || M!=0)) {
		tmp = N*(M-1ULL); 
		for (i=1; i<MAXL && tmp >= L[i]; i++) tmp -= L[i];
		cout << "Case " << t++ << ": " << find(tmp, i);
		
		tmp = N*(M-1ULL) + N-1ULL;
		for (i=1; i<MAXL && tmp >= L[i]; i++) tmp -= L[i];
		cout << ' ' << find(tmp, i) << endl;
	}

	return 0;
}
