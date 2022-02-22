#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 131072

long long n[2][MAXN], m[2][MAXN];

bool simulate(long long c[2][MAXN], int N0, int N1) {
    int N[2] = {N0, N1}, cur, next, res;

    cur = 1; res = -1;
    while (N[0] > 1 && N[1] > 1 && res == -1) {
//        for (int i=0; i<2; i++) {for (int j=0; j<=N[i]; j++) cout << c[i][j] << ' '; cout << endl;} cout << endl;
        next = 1-cur;
        if (c[cur][N[cur]] > c[next][N[next]]) res = cur;
        else {c[cur][N[cur]-1] += c[cur][N[cur]]; N[cur]--;}
        cur = next;
    }
    if (res == -1) {
//        for (int i=0; i<2; i++) {for (int j=0; j<=N[i]; j++) cout << c[i][j] << ' '; cout << endl;} cout << endl;
        next = 1-cur;
        if (c[cur][N[cur]] > c[next][N[next]]) res = cur;
        else if (N[cur] == 1) res = next;
        else {
            c[cur][N[cur]-1] += c[cur][N[cur]]; N[cur]--;
            if (c[next][1] > c[cur][N[cur]]) res = next;
            else res = cur;
        }
    }
//    cout << res << endl;
    return res == 0;
}

int main() {
    int N[2], i, j;

    int CASE = 1;
    while (cin >> N[0] >> N[1]) {
        n[0][0] = n[1][0] = 0LL;
        for (i=0; i<2; i++) {
            for (j=1; j<=N[i]; j++) cin >> n[i][j];
            sort(n[i], n[i]+1+N[i]);
            for (j=0; j<=N[i]; j++) m[i][j] = n[i][j];
        }
        m[0][N[0]-1] += m[0][N[0]];

        bool flag = false;
        if (N[0] > 1) flag |= simulate(m, N[0]-1, N[1]);
        if (n[0][N[0]] > n[1][N[1]]) flag |= simulate(n, N[0], N[1]-1);

        cout << "Case " << CASE++ << ": ";
        if (!flag) cout << "Buyout Limited" << endl;
        else cout << "Takeover Incorporated" << endl;
    }

    return 0;
}
