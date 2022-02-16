#include <iostream>
#include <algorithm>
using namespace std;

struct triangle {
    int id[3];
} tt[32];

bool operator<(const triangle &t1, const triangle &t2) {
    if (t1.id[0] != t2.id[0]) return t1.id[0] < t2.id[0];
    else if (t1.id[1] != t2.id[1]) return t1.id[1] < t2.id[1];
    else return t1.id[2] < t2.id[2];
}

int main() {
    int T, t, N, n[32], i, next[32], prev[32], TT, ID;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> N;
        for (i=0; i<N; i++) {
            cin >> n[i];
            next[i] = (i+1)%N;
            prev[i] = (i+N-1)%N;
        }

        TT = 0;
        while (TT < N-2) {
            for (i=0; i<N; i++) if (n[i] == 1) break;
            if (i == N || !n[next[i]] || !n[prev[i]]) break;

            tt[TT].id[0] = i;
            tt[TT].id[1] = next[i];
            tt[TT].id[2] = prev[i];
            sort(tt[TT].id, tt[TT].id+3); TT++;

            n[i]--; n[next[i]]--; n[prev[i]]--;
            next[prev[i]] = next[i];
            prev[next[i]] = prev[i];
        }
        if (TT < N-2) cout << ID << " N" << endl;
        else {
            cout << ID << " Y" << endl;
            sort(tt, tt+TT);
            for (i=0; i<TT; i++) cout << tt[i].id[0]+1 << ' ' << tt[i].id[1]+1 << ' ' << tt[i].id[2]+1 << endl;
        }
    }

    return 0;
}
