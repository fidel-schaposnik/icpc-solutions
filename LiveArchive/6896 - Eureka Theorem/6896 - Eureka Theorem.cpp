#include <iostream>
using namespace std;

int main() {
	int T, t, N, i, j, k;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		
		bool flag = false;
		for (i=1; i*(i+1)/2<N; i++)
			for (j=i; j*(j+1)/2<N; j++)
				for (k=j; k*(k+1)/2<N; k++)
					if (i*(i+1)/2+j*(j+1)/2+k*(k+1)/2 == N)
						flag = true;
		if (flag) cout << 1 << endl;
		else cout << 0 << endl;
	}

	return 0;
}
