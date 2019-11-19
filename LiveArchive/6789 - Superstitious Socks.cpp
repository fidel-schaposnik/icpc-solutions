#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 131072
#define INF 1000000000

int n[MAXN], N;

long long cant(int d) {
	int i = 0, j = 0;
	long long RES = 0LL;
	
	while (i < N) {
		if (j < N && n[j]-n[i] < d) j++;
		else {
			RES += j-i-1;
			i++;
		}
	}
	return RES;
}

void find(int d, int K) {
	int i = 0, j = 0;
	while (i < N) {
		if (j < N && n[j]-n[i] < d) j++;
		else {
			if (n[j]-n[i] == d) {
				K--;
				if (!K) { cout << n[i] << ' ' << n[j] << endl; return; }
			}
			i++;
		}
	}
}

int main() {
	int K, i, s, e, m;
	
	while (cin >> N >> K && (N || K)) {
		for (i=0; i<N; i++) cin >> n[i];
		sort(n, n+N);
		
		s = 1; e = INF;
		while (e-s > 1) {
			m = (s+e)/2;
			if (cant(m) < K) s = m;
			else e = m;
		}
		find(s, K-cant(s));
	}

	return 0;
}
