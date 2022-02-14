#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 20
#define MAXS 5000000
#define INF 1000000000

typedef unsigned int mask;

int dp[2][1<<MAXN][MAXN], N, w[MAXN][MAXN], BEST;

struct state {
    mask m;
    int last;
} s[MAXS];

void fill(int cur, int start, int cant) {
    int S, E, curn, i, COUNT;
    mask curm;

    dp[cur][1<<start][start] = 0;
    s[0].m = 1<<start; s[0].last = start;
    S = 0; E = 1;
    while (S < E) {
        curn = s[S].last;
        curm = s[S].m;
        S++;

        COUNT = 0;
        for (i=0; i<N; i++) if (((curm>>i)&1) == 1) COUNT++;
        if (COUNT == cant) continue;

        for (i=0; i<N; i++) {
            if (((curm>>i)&1) == 0) {
                if (dp[cur][curm^(1<<i)][i] == -1) {
                    dp[cur][curm^(1<<i)][i] = dp[cur][curm][curn]+w[curn][i];
                    s[E].m = curm^(1<<i);
                    s[E].last = i;
                    E++;
                } else if (dp[cur][curm^(1<<i)][i] > dp[cur][curm][curn]+w[curn][i]) dp[cur][curm^(1<<i)][i] = dp[cur][curm][curn]+w[curn][i];
            }
        }
    }
}

void dfs(int pos, mask curm, int CANT) {
    if (pos < N-1 && CANT > 0) {
        dfs(pos+1, curm, CANT);
        dfs(pos+1, curm^(1<<pos), CANT-1);
    } else if (CANT == 0) {
        mask nextm = ((1<<(N-1))-1)^curm^1;
        int tmp_ida, tmp_vuelta, i, j;

        tmp_ida = tmp_vuelta = INF;
        for (i=1; i<N-1; i++) {
            if (((curm>>i)&1) == 0) continue;

            for (j=1; j<N-1; j++) {
                if (((nextm>>j)&1) == 0) continue;
    
                tmp_ida = min(tmp_ida, dp[0][curm^1][i] + w[i][j] + dp[1][nextm^(1<<(N-1))][j]);
                tmp_vuelta = min(tmp_vuelta, dp[1][curm^(1<<(N-1))][i] + w[i][j] + dp[0][nextm^1][j]);
            }
        }
        BEST = min(BEST, tmp_ida+tmp_vuelta);
    }
}

int main() {
    int E, i, j, k, a, b, tmp, t;

    t = 1;
    while (cin >> N >> E) {
        for (i=0; i<N; i++) for (j=0; j<N; j++) w[i][j] = INF;
        for (i=0; i<E; i++) {
            cin >> a >> b >> tmp;
            w[a][b] = w[b][a] = tmp;
        }
    
        for (k=0; k<N; k++) for (i=0; i<N; i++) for (j=0; j<N; j++) w[i][j] = min(w[i][j], w[i][k]+w[k][j]);
    
        memset(dp, -1, sizeof(dp));
        fill(0, 0, N/2 + N%2);
        fill(1, N-1, N/2 + N%2);
    
        BEST = INF;
        dfs(1, 0, (N-2)/2);
        if (N == 3) BEST = min(BEST, 2*(w[0][1]+w[1][2]));
        cout << "Case " << t++ << ": " << BEST << endl;
    }

    return 0;
}
