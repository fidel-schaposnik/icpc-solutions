#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 32
#define INF 1000000000000000000LL

typedef unsigned long long HASH;

int POS;
char input[MAXN], a[MAXN], b[MAXN];

HASH modexp(HASH h, long long exp) {
	HASH RES = 1ULL;
	while (exp) {
		if (exp&1LL) RES = RES*h;
		h = h*h;
		exp >>= 1;
	}
	return RES;
}

HASH repeat(HASH h, long long len, long long exp) {
	HASH RES = 0ULL, BASE = modexp(33ULL, len);
	while (exp) {
		if (exp&1LL) RES = RES*BASE + h;
		h = h*BASE+h;
		BASE = BASE*BASE;
		exp >>= 1;
	}
	return RES;
}

pair<HASH, int> expr(long long CANT) {
	int LEN = 0;
	HASH RES = 0ULL;
	while (CANT && input[POS] != ']' && input[POS] != '\0') {
		if (input[POS] == '[') {
			POS++; int START = POS;
			pair<HASH, int> tmp = expr(INF);
			POS++;
			
			long long len = 0LL;
			while (input[POS] >= '0' && input[POS] <= '9') { len = len*10LL + input[POS++]-'0'; }
			
			long long rep = CANT/tmp.second;
			if (rep >= len) {
				RES = RES*modexp(33ULL, tmp.second*len) + repeat(tmp.first, tmp.second, len);
				LEN += tmp.second*len;
				CANT -= tmp.second*len;
			} else {
				RES = RES*modexp(33ULL, tmp.second*rep) + repeat(tmp.first, tmp.second, rep);
				LEN += tmp.second*rep;
				CANT -= tmp.second*rep;
				
				POS = START;
				tmp = expr(CANT);
				RES = RES*modexp(33ULL, tmp.second) + tmp.first;
				LEN += tmp.second;
				CANT -= tmp.second;
			}
		} else {
			while (CANT && input[POS] >= 'a' && input[POS] <= 'z') {
				RES = RES*33ULL + input[POS++]-'a';
				LEN++; CANT--;
			}
		}
	}
	return make_pair(RES, LEN);
}

bool check(long long CANT) {
	pair<HASH, int> A, B;
	
	memcpy(input, a, MAXN); POS = 0;
	A = expr(CANT);
		
	memcpy(input, b, MAXN); POS = 0;
	B = expr(CANT);
	
	return A == B;
}

int main() {
	int T, t;
	long long s, e, m;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> a >> b;

		cout << "Case #" << t << ": ";
		if (check(INF)) cout << "YES" << endl;
		else {
			s = 0LL; e = INF;
			while (e-s > 1) {
				m = (s+e)/2LL;
				if (check(m)) s = m;
				else e = m;
			}
			cout << "NO " << e << endl;
		}
	}
	
	return 0;
}
