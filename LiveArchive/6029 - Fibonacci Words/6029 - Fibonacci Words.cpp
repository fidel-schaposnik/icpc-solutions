#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAXP 110000
#define MAXN 110

typedef unsigned long long HASH;

#define VALUE(c) ( (c)=='0' ? 3ULL : 5ULL )
#define BASE 17ULL

int P, len[32];
HASH pow[MAXP], hp, r[MAXN][MAXP], l[MAXN][MAXP], h[32];
bool dr[MAXN][MAXP], dl[MAXN][MAXP];
long long cant[MAXN];

HASH _r(int n, int c) {
    if (n < 32 && c == len[n]) return h[n];

    if (!dr[n][c]) {
        if (n-2 < 32 && len[n-2] < c) r[n][c] = _r(n-1, c-len[n-2])*pow[len[n-2]] + h[n-2];
        else r[n][c] = _r(n-2, c);
        dr[n][c] = true;
    }
    return r[n][c];
}

HASH _l(int n, int c) {
    if (n < 32 && c == len[n]) return h[n];

    if (!dl[n][c]) {
        if (n-1 < 32 && len[n-1] < c) l[n][c] = h[n-1]*pow[c-len[n-1]] + _l(n-2, c-len[n-1]);
        else l[n][c] = _l(n-1, c);
        dl[n][c] = true;
    }
    return l[n][c];
}

long long _cant(int n) {
    if (n<0 || (n<32 && len[n] < P)) return 0;
    else if (n < 32 && len[n] == P) return ( h[n]==hp ? 1 : 0 );

    if (cant[n] == -1) {
        cant[n] = _cant(n-1) + _cant(n-2);
        for (int i=1; i<=P-1; i++) {
            if ((n-1 < 32 && len[n-1] < i) || (n-2 < 32 && len[n-2] < P-i)) continue;

            if (_r(n-1, i)*pow[P-i] + _l(n-2, P-i) == hp) cant[n]++;
        }
    }
    return cant[n];
}

int main() {
    int n, i, CASE;
    string p;

    len[0] = len[1] = 1;
    for (i=2; i<32; i++) len[i] = len[i-1]+len[i-2];

    pow[0] = 1LL;
    for (i=1; i<MAXP; i++) pow[i] = pow[i-1]*BASE;

    h[0] = VALUE('0'); h[1] = VALUE('1');
    for (i=2; i<32 && len[i-2] < MAXP; i++) h[i] = h[i-1]*pow[len[i-2]] + h[i-2];

    memset(dl, false, sizeof(dl));
    memset(dr, false, sizeof(dr));

    CASE = 1;
    while (cin >> n >> p) {
        P = p.size();

        hp = 0;
        for (i=0; i<(int)p.size(); i++) hp = hp*BASE + VALUE(p[i]);

        memset(cant, -1, sizeof(cant));
        cout << "Case " << CASE++ << ": " << _cant(n) << endl;
    }


    return 0;
}
