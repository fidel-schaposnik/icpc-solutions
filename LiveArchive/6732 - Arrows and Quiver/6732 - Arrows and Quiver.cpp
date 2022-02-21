#include <iostream>
#include <cstring>
using namespace std;

#define MAXM 131072
#define MAXN 131072

int m[MAXM], M, cant[MAXN];

int timer(int K) {
    int i, j, RES, CUR;

    memset(cant, 0, sizeof(cant));
    i = j = RES = CUR = 0;
    while (j<M) {
        if (!cant[m[j]]) { RES++; CUR++; }
        cant[m[j]]++;
        while (CUR > K) {
            cant[m[i]]--;
            if (!cant[m[i]]) CUR--;
            i++;
        }
        j++;
    }
    return RES;
}

int main() {
    int N, C, s, e, mid, i, t, T;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> N >> M >> C;
        for (i=0; i<M; i++) cin >> m[i];
    
        if (timer(N) > C) cout << -1 << endl;
        else {
            s = 0; e=N;
            while (e-s > 1) {
                mid = (s+e)/2;
                if (timer(mid) > C) s = mid;
                else e = mid;
            }
            cout << e << endl;
        }
    }

    return 0;
}
