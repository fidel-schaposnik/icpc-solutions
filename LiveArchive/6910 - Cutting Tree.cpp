#include <iostream>
using namespace std;

#define MAXN 32768
#define MAXK 8192

int f[MAXN], p[MAXN], c[MAXN], x[MAXK], y[MAXK];
char q[MAXK];
bool ans[MAXK];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

void join(int a, int b) {
	int fa = getf(a), fb = getf(b);
	f[fa] = fb;
}

int main() {
	int T,  t, N, K, i;
	
	cin >> T;
	for (t=1; t<=T; t++) {
		cin >> N >> K;
		for (i=1; i<=N; i++) {
			cin >> p[i];
			f[i] = i;
			c[i] = 1;
		}
		
		for (i=0; i<K; i++) {
			cin >> q[i] >> x[i];
			if (q[i] == 'C') c[x[i]]--;
			else cin >> y[i];
		}
		
		for (i=1; i<=N; i++) if (c[i] == 1 && p[i]) join(i, p[i]);
		
		for (i=K-1; i>=0; i--) {
			if (q[i] == 'C') {
				c[x[i]]++;
				if (c[x[i]] == 1 && p[x[i]]) join(x[i], p[x[i]]);
			} else if (getf(x[i]) == getf(y[i])) ans[i] = true;
			else ans[i] = false;
		}
		
		cout << "Case #" << t << ":" << endl;
		for (i=0; i<K; i++) if (q[i] == 'Q') cout << ( ans[i] ? "YES" : "NO" ) << endl;
	}
	
	return 0;
}
