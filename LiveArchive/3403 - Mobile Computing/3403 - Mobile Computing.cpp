#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define MIN(x,y) ( (x)<(y) ? (x) : (y) )
#define MAX(x,y) ( (x)>(y) ? (x) : (y) )

typedef long double tint;

int w[64], s[6], S, c[64];

void dfsw(int m, int cant, int pos, int curw) {
   if (pos == S) {w[m] = curw; c[m] = cant;}
	else {
		dfsw(m, cant, pos+1, curw);
		dfsw(m^(1<<pos), cant+1, pos+1, curw+s[pos]);
	}
}

struct par {
   tint l, r;
} tmp;

int CANT;

vector<par> dfs(tint x, int m, int lvl) {
/*	cout << "llamando en la posicion " << x << " con la mascara ";
	for (int i=0; i<S; i++) cout << ((m>>i)&1);
	cout << endl;*/

   if (c[m] == 1) {
		vector<par> RES;
		tmp.l = x; tmp.r = x;
		RES.push_back(tmp);
		return RES;
	} else {
		vector<par> tmp1, tmp2, RES;
		for (int i=1; i<(1<<S); i++) {
			if ((i&m) == i && i != m) {
				tmp1 = dfs(x+((tint)w[m^i])/((tint)(w[i] + w[m^i])), i, lvl+1);
				tmp2 = dfs(x-((tint)w[i])/((tint)(w[i] + w[m^i])), m^i, lvl+1);

				for (int j=0; j<tmp1.size(); j++) {
					for (int k=0; k<tmp2.size(); k++) {
						tmp.l = MIN(tmp1[j].l, tmp2[k].l);
						tmp.r = MAX(tmp1[j].r, tmp2[k].r);
						RES.push_back(tmp);
					}
				}
			}
		}
		return RES;
	}
}

int main() {

tint R, BEST;
int i, k, K;

cin >> K;

for (k=0; k<K; k++) {

cin >> R;
cin >> S;
for (i=0; i<S; i++) {
   cin >> s[i];
}
dfsw(0, 0, 0, 0);

/*for (i=0; i<(1<<S); i++) {
   for (int j=0; j<S; j++) cout << ((i>>j)&1);
	cout << ' ' << c[i] << ' ' << w[i] << endl;
}*/

CANT = 0;
vector<par> RES = dfs(0.0, (1<<S)-1, 0);

BEST = -1.0;
for (i=0; i<RES.size(); i++) {
   if (RES[i].r-RES[i].l < R && RES[i].r-RES[i].l > BEST) BEST = RES[i].r-RES[i].l;
}
if (BEST > -0.5) printf("%.16lf\n", (double)BEST);
else cout << "-1" << endl;

}

return 0;
}
