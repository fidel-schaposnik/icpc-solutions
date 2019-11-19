#include <iostream>
using namespace std;

#define MAXN 30000100

int c[MAXN];

int main() {
    int d, k, A, B, N, t, T, i;
    
    for (d=1; d<MAXN; d++) for (k=2; k<MAXN/d; k++) {        
       A = k*d;
       if (((A+d)^A) == d) c[A+d]++;
    }
    for (i=1; i<MAXN; i++) c[i] += c[i-1];

   cin >> T;
   for (t=1; t<=T; t++) {
       cin >> N;
       cout << "Case " << t << ": " << c[N] << endl;
   }

    return 0;
}
