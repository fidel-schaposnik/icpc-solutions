#include <iostream>
using namespace std;

#define MOD 10000000000007

int main() {
	int L, M, N, T, t, i;
	long long RES, cur;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> L >> M >> N;
		
		RES = 0LL; cur = 1LL;
		for (i=1; i<=N; i++) {
			cur = (cur*(L*L-i+1LL))%MOD;
			if (i >= M) RES = (RES + cur)%MOD;
		}
		cout << "Case " << t << ": " << RES << endl;
	}

	return 0;
}
