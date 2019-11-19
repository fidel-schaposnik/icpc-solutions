
#include <iostream>
using namespace std;

#define INF 1000000000
#define MAXN 65536

int s[MAXN];

int main() {
	int T, t, N, i, a, b;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N; 
		
		a = b = -1;
		for (i=2; i*i<=2*N; i++) if ((2*N)%i == 0) if ( ((2*N)/i-i-1)%2 == 0) { 
			a = ((2*N)/i-i-1)/2; b = a+i;
			break;
		}
		if (a == -1 && b == -1) cout << "IMPOSSIBLE" << endl;
		else {
			cout << N << " =";
			for (i=a+1; i<=b; i++) cout << ' ' << i << (i<b ? " +" : "");
			cout << endl;
		}
	}

	return 0;
}
