#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 512

int sx[MAXN*MAXN], sy[MAXN*MAXN], d[MAXN][MAXN];
char m[MAXN][MAXN];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    int N, M, i, j, S, E, x, y, Ex, Ey, T, t;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> N >> M;
        for (i=0; i<=N+1; i++) m[i][0] = m[i][M+1] = '*';
        for (j=0; j<=M+1; j++) m[0][j] = m[N+1][j] = '*';
    
        for (i=1; i<=N; i++) for (j=1; j<=M; j++) cin >> m[i][j];
        cin >> sx[0] >> sy[0] >> Ex >> Ey;
    
        memset(d, -1, sizeof(d));
        d[sx[0]][sy[0]] = 0;
    
        S = 0; E = 1;
        while (S < E) {
            x = sx[S]; y = sy[S++];
            for (i=0; i<4; i++) {
                if (m[x+dx[i]][y+dy[i]] == 'x') m[x+dx[i]][y+dy[i]] = '.';
                else if (m[x+dx[i]][y+dy[i]] == '*') m[x+dx[i]][y+dy[i]] = 'x';
    
                if (m[x+dx[i]][y+dy[i]] == '.' && d[x+dx[i]][y+dy[i]] == -1) {
                    d[x+dx[i]][y+dy[i]] = d[x][y]+1;
                    sx[E] = x+dx[i]; sy[E++] = y+dy[i];
                }
            }
        }
        if (d[Ex][Ey] != -1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}
