#include <iostream>
using namespace std;

#define MAX 131072

int e[MAX], p[MAX];

unsigned long long binomial(int n, int m) {
    unsigned long long RES = 1ULL;
    e[n]++; e[m]--; e[n-m]--;
    for (int i=n; i>2; i--) e[i-1] += e[i];
    for (int i=n; i>=2; i--) {
        if (p[i]) {e[p[i]] += e[i]; e[i/p[i]] += e[i]; e[i] = 0;}
        else while (e[i]) {RES *= i; e[i]--;}
    }
    return RES;
}

int main() {
    int T, t, ID, N, I, J, i, j;
    unsigned long long RES;

    for (i=4; i<MAX; i+=2) p[i] = 2;
    for (i=3; i*i<MAX; i+=2) if (!p[i]) for (j=i*i; j<MAX; j+=2*i) p[j] = i;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> N >> I >> J;
        if (I < J) cout << ID << ' ' << 0 << endl;
        else {
            RES = 1ULL;
            for (i=0; i<I-J; i++) RES *= N;
            cout << ID << ' ' << RES*binomial(I, J) << endl;
        }
    }

    return 0;
}
