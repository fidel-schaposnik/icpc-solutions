#include <iostream>
#include <map>
#include <cstring>
using namespace std;

#define MAXW 16
#define MAXH 16
#define MAXS 16777216

int _hash(int p[4][2], int N) {
	int RES = 0;
	for (int i=0; i<N; i++) for (int j=0; j<2; j++) RES = RES*10+p[i][j];
	return RES;
}

void unhash(int HASH, int p[4][2], int N) {
	for (int i=N-1; i>=0; i--) for (int j=1; j>=0; j--) {
		p[i][j] = HASH%10;
		HASH /= 10;
	}
}

int s[MAXS];
map<int, int> d;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
	int N, W, H, L, i, j, p[4][2], X, Y, S, E, cur, curd, x, y, tmpp[4][2], next;
	char m[MAXW][MAXH];
	
	while (cin >> N >> W >> H >> L) {
		for (j=0; j<H; j++) for (i=0; i<W; i++) {
			cin >> m[i][j];
			if (m[i][j] >= '1' && m[i][j] <= '4') {
				p[m[i][j]-'1'][0] = i;
				p[m[i][j]-'1'][1] = j;
				
			} else if (m[i][j] == 'X') {
				X = i; Y = j;
				m[i][j] = '.';
			}
		}
		
		S = E = 0; s[E++] = _hash(p, N);
		d.clear(); d[s[0]] = 0;
		while (S < E) {
			cur = s[S++];
			unhash(cur, p, N);
			curd = d[cur];
			if (p[0][0] == X && p[0][1] == Y) break;
			else if (curd == L) continue;

			for (i=0; i<N; i++) {
				for (j=0; j<N; j++) if (j != i) m[p[j][0]][p[j][1]] = '1'+i;
				for (int k=0; k<4; k++) {
					x = p[i][0]; y = p[i][1];
					while (x+dx[k] >= 0 && y+dy[k] >= 0 && x+dx[k] < W && y+dy[k] < H && m[x+dx[k]][y+dy[k]] == '.') { x += dx[k]; y += dy[k]; }
					memcpy(tmpp, p, sizeof(p));
					tmpp[i][0] = x;
					tmpp[i][1] = y;
					next = _hash(tmpp, N);
					if (d.find(next) == d.end()) {
						d[next] = curd+1;
						s[E++] = next;
					}
				}
				for (j=0; j<N; j++) if (j != i) m[p[j][0]][p[j][1]] = '.';
			}
		}
		
		if (S < E) cout << curd << endl;
		else cout << "NO SOLUTION" << endl;
	}
	
	return 0;
}
