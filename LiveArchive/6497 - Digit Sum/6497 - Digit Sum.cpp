#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N, i, j, k, n[16], c[2][16], C[2];
    long long BEST, tmp[2];
    bool flag;

    while (cin >> N && N) {
        for (i=0; i<N; i++) cin >> n[i];
    
        BEST = 1000000000000000000LL;
        for (i=1; i<(1<<N)-1; i++) {
            C[0] = C[1] = 0;
            for (j=0; j<N; j++) c[(i>>j)&1][C[(i>>j)&1]++] = n[j];
    
            flag = true;
            for (j=0; j<2; j++) {
                sort(c[j], c[j]+C[j]);
                if (c[j][0] == 0) {
                    for (k=1; k<C[j]; k++) if (c[j][k]) { swap(c[j][0], c[j][k]); break; }
                    if (k == C[j]) flag = false;
                }
    
                tmp[j] = 0LL;
                for (k=0; k<C[j]; k++) tmp[j] = tmp[j]*10LL + c[j][k];
            }
            if (flag) BEST = min(BEST, tmp[0]+tmp[1]);
        }
        cout << BEST << endl;
    }

    return 0;
}
