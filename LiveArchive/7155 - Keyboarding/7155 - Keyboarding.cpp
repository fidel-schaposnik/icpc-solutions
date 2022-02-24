#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define MAXN 55
#define MAXS 10010

int d[MAXN][MAXN][MAXS], sx[MAXS*MAXN*MAXN], sy[MAXS*MAXN*MAXN], sc[MAXS*MAXN*MAXN];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int main() {
	int R, C, i, j, x, y, c, S, E, xp, yp;
	char key[MAXN][MAXN];
	bool valid[MAXN][MAXN];
	string s;
	
	while (cin >> R >> C) {
		for (i=1; i<=R; i++) for (j=1; j<=C; j++) cin >> key[i][j];
		cin >> s; s += '*';
		
		memset(valid, true, sizeof(valid));
		for (i=0; i<=R+1; i++) valid[i][0] = valid[i][C+1] = false;
		for (j=0; j<=C+1; j++) valid[0][j] = valid[R+1][j] = false;
		
		memset(d, -1, sizeof(d)); d[1][1][0] = 0;
		S = E = 0; sx[E] = 1; sy[E] = 1; sc[E++] = 0;
		while (S < E) {
			x = sx[S]; y = sy[S]; c = sc[S++];
			if (c == (int)s.size()) break;
			
			if (s[c] == key[x][y]) {
				d[x][y][c+1] = d[x][y][c]+1;
				sx[E] = x; sy[E] = y; sc[E++] = c+1;
			} else {
				for (i=0; i<4; i++) {
					xp = x+dx[i]; yp = y+dy[i];
					while (valid[xp][yp] && key[xp][yp] == key[x][y]) { xp += dx[i]; yp += dy[i]; }
					if (valid[xp][yp] && d[xp][yp][c] == -1) {
						d[xp][yp][c] = d[x][y][c]+1;
						sx[E] = xp; sy[E] = yp; sc[E++] = c;
					}
				}
			}
		}
		cout << d[x][y][c] << endl;
	}

	return 0;
}
