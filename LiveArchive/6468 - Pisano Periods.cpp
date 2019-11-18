#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXP 1048576

//int p[MAXP];

//int fact(int n, int f[]) {
//    int F = 0;
//    while (p[n]) {
//        f[F++] = p[n];
//        n /= p[n];
//    }
//    f[F++] = n;
//    return F;
//}
//
//int gcd(int a, int b) {
//    if (!b) return a;
//    else return gcd(b, a%b);
//}
//
//int lcm(int a, int b) {
//    return a*(b/gcd(a,b));
//}

map< pair<int, int>, int > v;

int period(int p, int n) {
    pair<int, int> tmp = make_pair(p, n);
    int f[2], cur, MOD, CANT;

    MOD = 1;
    for (int i=0; i<n; i++) MOD *= p;

    if (v.find(tmp) == v.end()) {
        cur = 0; f[0] = 0; f[1] = 1; CANT = 1;
        do {
            f[cur] = (f[0]+f[1])%MOD;
            cur = 1-cur;
            CANT++;
        } while (f[0]+f[1] > 1);
        v[tmp] = CANT;
    }
    return v[tmp];
}

int main() {
    int i, j, F, f[32], t, T, ID, N, RES;

//    for (i=4; i<MAXP; i+=2) p[i] = 2;
//    for (i=3; i*i<MAXP; i+=2) if (!p[i]) for (j=i*i; j<MAXP; j+=2*i) p[j] = i;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> N;
        cout << ID << ' ' << period(N, 1) << endl;

//        F = fact(N, f);
//        sort(f, f+F);
//
//        i = j = 0; RES = 1;
//        while (i < F) {
//            for (j=i; j<F && f[i]==f[j]; j++);
//            RES = lcm(RES, period(f[i], j-i));
//            i = j;
//        }
//        cout << ID << ' ' << RES << endl;
    }

    return 0;
}
