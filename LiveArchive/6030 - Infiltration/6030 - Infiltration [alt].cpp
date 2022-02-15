#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 128

int RES, cur[8], CUR, N, res[8];

struct mask {
    unsigned long long m[2];

    mask(unsigned long long m0=0ULL, unsigned long long m1=0ULL) {
        m[0] = m0; m[1]=m1;
    }

    bool full() {
        if (N >= 64) return m[0]==18446744073709551615ULL && m[1]==(1ULL<<(N-64))-1;
        else return m[0]==(1ULL<<N)-1;
    }

    void clear() {
        m[0] = m[1] = 0ULL;
    }

    void set(int pos) {
        if (pos >= 64) m[1] |= (1ULL<<(pos-64));
        else m[0] |= (1ULL<<pos);
    }
} n[MAXN];

mask orm(const mask &m1, const mask &m2) {
    return mask((m1.m[0]|m2.m[0]), (m1.m[1]|m2.m[1]));
}

void dfs(int pos, mask curm) {
    if (curm.full()) {RES = CUR; memcpy(res,cur,sizeof(cur));}
    
    if (pos < N && CUR+1 < RES) {
        cur[CUR++] = pos;
        dfs(pos+1, orm(curm, n[pos]));
        CUR--;

        dfs(pos+1, curm);
    }
}

int main() {
    int i, j, CASE;
    char tmps[MAXN];

    CASE = 1;
    while (cin >> N) {
    
        for (i=0; i<N; i++) {
            cin >> tmps;
            n[i].clear();
            for (j=0; j<N; j++) if (j == i || tmps[j] == '1') n[i].set(j);
        }
    
        RES = 7; CUR = 0;
        dfs(0, mask());
        cout << "Case " << CASE++ << ": " << RES;
        for (i=0; i<RES; i++) cout << ' ' << res[i]+1; cout << endl;
    }

    return 0;
}
