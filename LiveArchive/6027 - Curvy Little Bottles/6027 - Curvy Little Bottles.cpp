#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

typedef double tint;

#define MAXN 32
#define EPS 1E-9

const tint pi = 2.0*acos(0.0);

int mul(tint *p, int P, tint *q, int Q, tint *r) {
    for (int i=0; i<MAXN; i++) r[i] = 0.0;
    for (int i=0; i<=P; i++) for (int j=0; j<=Q; j++) r[i+j] += p[i]*q[j];
    return P+Q;
}

tint eval(tint *p, int P, tint x) {
    tint RES = 0.0, xp = 1.0;
    for (int i=0; i<=P; i++) {
        RES += p[i]*xp;
        xp *= x;
    }
    return RES;
}

int integrate(tint *p, int P, tint x0, tint p0) {
    for (int i=P+1; i>0; i--) p[i] = p[i-1]/((tint)i);
    p[0] = 0.0;
    p[0] = p0 - eval(p, P+1, x0);
    return P+1;
}

tint findx(tint *p, int P, tint s, tint e, tint obj) {
    while (e-s > EPS) {
        tint m = (s+e)/2.0;
        if (eval(p, P, m) > obj) e = m;
        else s = m;
    }
    return (s+e)/2.0;
}

int main() {
    int P, i, t;
    tint p[MAXN], x_min, x_max, inc, r[MAXN], R, vol;

    t = 1;
    while (cin >> P) {
        for (i=0; i<=P; i++) cin >> p[i];
        cin >> x_min;
        cin >> x_max;
        cin >> inc;
    
        R = mul(p, P, p, P, r);
    
        R = integrate(r, R, x_min, 0.0);
    
        vol = pi*eval(r, R, x_max);
        printf("Case %d: %.2lf\n", t++, vol);
        if (vol < inc) cout << "insufficient volume" << endl;
        else {
            bool flag = false;
            for (i=1; i<=8 && inc*i<vol; i++) {
                if (flag) cout << ' ';
                else flag = true;
                printf("%.2lf", findx(r, R, x_min, x_max, inc*i/pi)-x_min);
            }
            cout << endl;
        }
    }

    return 0;
}
