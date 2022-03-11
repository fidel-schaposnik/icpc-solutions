#include <iostream>
#include <cstring>
using namespace std;

#define INF 1000000000000LL

typedef long long tint;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

struct edge {
   int s, e;
   tint w;
} e[8192];

int main() {

int X, Y, m[32][32], G, i, j, x, y, N, d, E, A;
tint dist[1024];
bool v[32][32], hash[32][32];

cin >> X;
cin >> Y;

do {

memset(v, true, sizeof(v));
for (i=0; i<=X+1; i++) v[i][0] = v[i][Y+1] = false;
for (j=0; j<=Y+1; j++) v[0][j] = v[X+1][j] = false;

N = 0;
for (j=1; j<=Y; j++) {
   for (i=1; i<=X; i++) {
	   m[i][j] = N;
		dist[N] = INF;
		N++;
   }
}
dist[m[1][1]] = 0;

cin >> G;
for (i=0; i<G; i++) {
   cin >> x; x++;
	cin >> y; y++;
	v[x][y] = false;
}

cin >> A;

E = 0;
memset(hash, false, sizeof(hash));
for (i=0; i<A; i++) {
	cin >> x; x++;
	cin >> y; y++;
	e[E].s = m[x][y];
	
	hash[x][y] = true;

	cin >> x; x++;
	cin >> y; y++;
	e[E].e = m[x][y];

	cin >> e[E].w;
	E++;
}

for (i=1; i<=X; i++) {
   for (j=1; j<=Y; j++) {
		if ((i==X && j==Y) || (hash[i][j] == true)) continue;
	   for (d=0; d<4; d++) {
		   if (v[i][j] == true && v[i+dx[d]][j+dy[d]] == true) {
			   e[E].s = m[i][j];
			   e[E].e = m[i+dx[d]][j+dy[d]];
				e[E].w = 1LL;
				E++;
			}
		}
	}
}

for (i=0; i<N; i++) {
   for (j=0; j<E; j++) {
	   if (dist[e[j].s] < INF && (dist[e[j].e] == INF || dist[e[j].e] > dist[e[j].s] + e[j].w)) {
		   dist[e[j].e] = dist[e[j].s] + e[j].w;
		}
	}
}

for (j=0; j<E; j++) {
   if (dist[e[j].s] < INF && dist[e[j].e] > dist[e[j].s] + e[j].w) {
	   cout << "Never" << endl;
		break;
	}
}
if (j == E) {
   if (dist[m[X][Y]] == INF) cout << "Impossible" << endl;
	else cout << dist[m[X][Y]] << endl;
}

cin >> X;
cin >> Y;

} while (X!=0 || Y!=0);

return 0;
}
