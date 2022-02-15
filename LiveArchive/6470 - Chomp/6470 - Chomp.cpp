#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 128

int dp[MAXN][MAXN][MAXN], col[MAXN][MAXN][MAXN], row[MAXN][MAXN][MAXN];

int _dp(int a, int b, int c) {
    if (dp[a][b][c] == -1) {
        dp[a][b][c] = 0;
        for (int i=0; !dp[a][b][c] && i<c; i++) if (!_dp(a, b, i)) { dp[a][b][c] = 1; col[a][b][c] = i; row[a][b][c] = 3; }
        for (int i=0; !dp[a][b][c] && i<b; i++) if (!_dp(a, i, min(i,c))) { dp[a][b][c] = 1; col[a][b][c] = i; row[a][b][c] = 2; }
        for (int i=1; !dp[a][b][c] && i<a; i++) if (!_dp(i, min(i,b), min(i,c))) { dp[a][b][c] = 1; col[a][b][c] = i; row[a][b][c] = 1; }
    }
    return dp[a][b][c];
}

int main() {
    int T, t, ID, a, b, c;

    memset(dp, -1, sizeof(dp));
    dp[1][0][0] = 0;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> a >> b >> c;
        cout << ID << ' ' << (_dp(a, b, c) ? 'W' : 'L');
        if (_dp(a, b, c)) cout << ' ' << col[a][b][c]+1 << ' ' << row[a][b][c];
        cout << endl;
    }

    return 0;
}
