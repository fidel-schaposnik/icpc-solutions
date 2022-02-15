#include <iostream>
using namespace std;

int main() {
    int T, t, ID, n[15], i, j, k, tmp, RES;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID;
        for (i=0; i<15; i++) cin >> n[i];

        RES = 0;
        for (i=1; i<14; i++) for (j=i+1; j<15; j++) {
            tmp = 1000000000;
            for (k=i; k<j; k++) tmp = min(tmp, n[k]);
            if (tmp > n[i-1] && tmp > n[j]) RES++;
        }
        cout << ID << ' ' << RES << endl;
    }

    return 0;
}
