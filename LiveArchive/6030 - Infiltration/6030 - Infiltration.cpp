#include <iostream>
using namespace std;

typedef unsigned long long mask;

#define MAXN 128

struct dmask {
    mask a, b;
} FULL, m[MAXN], BEST;

bool operator==(const dmask &m1, const dmask &m2) {
    return (m1.a==m2.a) && (m1.b==m2.b);
}

void operator|=(dmask &m1, const dmask &m2) {
    m1.a |= m2.a; m1.b |= m2.b;
}

void set(dmask &curm, int pos) {
    if (pos > 63) curm.b ^= (1ULL<<(pos-64));
    else curm.a ^= (1ULL<<pos);
}

bool isset(const dmask &curm, int pos) {
    if (pos > 63) return ((curm.b>>(pos-64))&1ULL);
    else return ((curm.a>>pos)&1ULL);
}

void clear(dmask &curm) {
    curm.a = curm.b = 0ULL;
}

int RES, N;

void greedy() {
    int i, j, LEFT, COUNT;
    dmask tmpm;

    clear(tmpm); clear(BEST); LEFT = N; RES = 0;
    while (LEFT > 0) {
        for (i=0; i<N; i++) {
            if (!isset(tmpm, i)) {
                COUNT = 0;
                for (j=0; j<N; j++) if (isset(m[i], j) && !isset(tmpm, j)) COUNT++;
                if (LEFT - COUNT <= COUNT) {
                    RES++;
                    LEFT -= COUNT;
                    tmpm |= m[i];
                    set(BEST, i);
                    break;
                }
            }
        }
    }
}

void dfs(dmask &curm, dmask &curs, int pos, int cant) {
    if (((cant+1 == RES) || (pos == N)) && (curm == FULL)) {
        RES = cant;
        BEST = curs;
    } else if (cant+1 < RES && pos < N) {
        dfs(curm, curs, pos+1, cant);
        dmask old_curm=curm, old_curs=curs;
        curm |= m[pos]; set(curs, pos);
        dfs(curm, curs, pos+1, cant+1);
        curm = old_curm; curs = old_curs;
    }
}

int main() {
    int i, j, t;
    char tmp;
    dmask tmpm1, tmpm2;

    t = 1;
    while (cin >> N) {
    
        clear(FULL);
        for (i=0; i<N; i++) {
            set(FULL, i); clear(m[i]);
            for (j=0; j<N; j++) {
                cin >> tmp;
                if (tmp == '1') set(m[i], j);
            }
        }
        for (i=0; i<N; i++) set(m[i], i);

        greedy();

        clear(tmpm1); clear(tmpm2);
        dfs(tmpm1, tmpm2, 0, 0);
    
        cout << "Case " << t++ << ": " << RES;
        for (i=0; i<N; i++) if (isset(BEST, i)) cout << ' ' << i+1;
        cout << endl;
    }

    return 0;
}
