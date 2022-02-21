#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 1000000000

int dp[4096][64], cant[4096], S;
bool ins[4096][64];

int _dp(int cur, int last) {
    if (cur == 0) return cant[0]-1;

    if (dp[cur][last] == -1) {
        dp[cur][last] = INF;
        for (int i=0; i<S; i++) if (ins[cur-1][i]) {
            if (ins[cur][i] && i != last || (i == last && cant[cur] == 1)) dp[cur][last] = min(dp[cur][last], _dp(cur-1, i) + cant[cur]-1);
            else dp[cur][last] = min(dp[cur][last], _dp(cur-1, i) + cant[cur]);
        }
    }
    return dp[cur][last];
}

int main() {
    int N[64], n[64][64], h[4096], H, i, j, ID, RES, h2i[16384];

    int CASE = 1;
    while (cin >> S) {
        H = 0;
        for (i=0; i<S; i++) {
            cin >> N[i];
            for (j=0; j<N[i]; j++) {
                cin >> n[i][j];
                h[H++] = n[i][j];
            }
        }
        sort(h, h+H);

        h2i[h[0]] = 0; ID = 1;
        for (i=1; i<H; i++) if (h[i] != h[i-1]) h2i[h[i]] = ID++;

        memset(ins, false, sizeof(ins));
        memset(cant, 0, sizeof(cant));
        for (i=0; i<S; i++) {
            for (j=0; j<N[i]; j++) {
                if (!ins[h2i[n[i][j]]][i]) {
                    ins[h2i[n[i][j]]][i] = true;
                    cant[h2i[n[i][j]]]++;
                }
            }
        }

        memset(dp, -1, sizeof(dp)); RES = INF;
        for (i=0; i<S; i++) if (ins[ID-1][i]) RES = min(RES, _dp(ID-1, i));
        cout << "Case " << CASE++ << ": " << 2*RES-S+1 << endl;
    }

    return 0;
}
