#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {

int R, D, A, K;

K = 1;

while (scanf("%d", &R) != EOF && R!=0) {
	if (K > 1) cout << endl;
	cout << "Test Rig " << K++ << endl;
   while (scanf("%d %d", &D, &A) != EOF && (D!=0 || A!=0)) {
      cout << (int)(D/(2.0*R*sin(acos(0.0)*A/90.0))) << endl;
   }
}

return 0;
}
