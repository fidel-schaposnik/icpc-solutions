#include <iostream>
#include <string>
using namespace std;

int main() {
	int N, i;
	string A, B;
	long long c11, c10, c00, c01;
	
	cin >> N >> B >> A;
	
	c11 = c10 = c00 = c01 = 0;
	for (i=0; i<N; i++) {
		if (A[i] == '1' && B[i] == '1') c11++;
		else if (A[i] == '1' && B[i] == '0') c10++;
		else if (A[i] == '0' && B[i] == '0') c00++;
		else if (A[i] == '0' && B[i] == '1') c01++;
	}
	
	cout << c11*c00 + c01*c00 + c10*c01 << endl;

	return 0;
}
