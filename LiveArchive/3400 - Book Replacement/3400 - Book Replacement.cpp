#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;


#define forn(i,n) for(int i = 0; i < (n); ++i)
#define forsn(i,m,n) for(int i = (m); i < (n); ++i)
#define si(a) (int)(a.size())
#define pb push_back
#define mp make_pair

#define MAXM 20
#define MAXN 128
#define MAXL 100000

list<int> d[MAXM];
queue<int> lib[MAXN], cola;
int pos[MAXL];
int k[MAXN], n, m, res, c, r;
map<int,int> g;

void sacar(int libro) {
	int u = pos[libro];
	res+= u+1;
	for(list<int>::iterator it = d[u].begin(); it!=d[u].end(); it++) if (*it==libro) {d[u].erase(it); break;}	
}

void poner(int libro) {
	if (si(d[0])<c) {
		d[0].pb(libro);
		res++;
		pos[libro] = 0;	
	} else {
		int i = 0;
		while (si(d[i])>=c && i<m) i++;
		d[i].pb(libro);
		res+= i+1;
		pos[libro] = i;
		
		int p = d[0].front(); d[0].pop_front();
		res++;
		
		i=1;
		while(si(d[i])>=c && i<m) i++;
		d[i].pb(p);
		res+= i+1;
		pos[p] = i;
		
		int u = pos[libro];
		for(list<int>::iterator it = d[u].begin(); it!=d[u].end(); it++) if (*it==libro) {d[u].erase(it); break;}
		res+= pos[libro]+1;
		
		d[0].pb(libro);
		res++;
		pos[libro] = 0;
	}
}

void init() {
	forn(i,MAXM) d[i].clear();
	forn(j,MAXN) while(!lib[j].empty()) lib[j].pop();	
	res = 0;
	r=0;
	g.clear();
}

int main () {
	while (cin >> m >> c >> n && (m || c || n)) {
		init();
		forn(i,n) {
			cin >> k[i];
			forn(j,k[i]) {
				int bij; cin >> bij;
				if (g.count(bij)==0) g[bij] = r++;
				lib[i].push(g[bij]);
			}
			cola.push(i);	
		}	
		forn(i,r) {
			pos[i] = m;
			d[m].pb(i);
		}
		
		while (!cola.empty()) {
			int p = cola.front(); cola.pop();
			int libro = lib[p].front(); lib[p].pop();
			if (!lib[p].empty()) cola.push(p);
			
			sacar(libro);
			poner(libro);
		}
		cout << res << endl;	
	}
	return 0;
}
