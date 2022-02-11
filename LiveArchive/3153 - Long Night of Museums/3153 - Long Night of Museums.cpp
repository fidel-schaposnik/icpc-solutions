#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAXN 20
#define INF 10000000

int N, n[MAXN], c[MAXN][MAXN], dp[1<<MAXN][MAXN];

int _dp(int m, int cur) {
    if (dp[m][cur] == -1) {
        dp[m][cur] = INF;
        for (int i=0; i<N; i++) if (i != cur && ((m>>i)&1) == 1) dp[m][cur] = min(dp[m][cur], _dp(m^(1<<cur), i)+c[i][cur]);
    }
    return dp[m][cur];
}

int main() {
    int i, j, cant, time, RES;

    while (scanf("%d", &N) != EOF && N) {
        for (i=0; i<N; i++) scanf("%d", &n[i]);
        for (i=0; i<N; i++) for (j=0; j<N; j++) scanf("%d", &c[i][j]);
    
        memset(dp, -1, sizeof(dp));
        for (i=0; i<N; i++) dp[1<<i][i] = 0;

        RES = 0;
        for (i=0; i<(1<<N); i++) {
            cant = time = 0;
            for (j=0; j<N; j++) if ((i>>j)&1) { cant++; time += n[j]; }
            if (cant <= RES || time > 7*60) continue;

            for (j=0; j<N; j++) if ((i>>j)&1) if (_dp(i, j)+time <= 7*60) RES = cant;
        }
        printf("%d\n", RES);
    }

    return 0;
}
