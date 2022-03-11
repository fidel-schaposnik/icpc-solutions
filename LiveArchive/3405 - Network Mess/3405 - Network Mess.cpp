#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef vector<int> vi;

#define forn(i,n) for(int i = 0; i < (n); ++i)
#define forsn(i,m,n) for(int i = (m); i < (n); ++i)
#define si(a) (int)(a.size())
#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()

#define MAXN 100

int n, d[MAXN][MAXN];
vi rout;

void init(){
	rout.clear();
}

int resta(int nh){ //se puede optimizar
	forn(i, n){
		if(i == nh) continue;
		d[i][nh]--; d[nh][i]--;
	}			
	rout.pb(2);
}

int mergea(int nh, vi lista){
	bool isin[MAXN];
	int dtmp[MAXN][MAXN];
	
	//cout << "mergeando " << nh << " con ";
	//forn(i, si(lista)) cout << lista[i] << " "; cout << endl;
	
	memset(isin, false, sizeof(isin));
	forn(i, si(lista)) isin[lista[i]] = true;	
	int ind[MAXN], itmp = 0;
	forn(i, n){ if(!isin[i]) ind[i] = itmp++; }
	//cout << itmp << endl;
	if(itmp) rout.pb(si(lista)+1);
	else rout.pb(si(lista));
	
	forn(i, n){
		if(isin[i]) continue;
		forn(j, n){
			if(isin[j]) continue;
			dtmp[ind[i]][ind[j]] = d[i][j];
		}
	}
	forn(i, n){
		if(isin[i]) continue;
		dtmp[ind[i]][itmp] = dtmp[itmp][ind[i]] = d[i][nh]-1;
	}
	if(itmp!=0)itmp++;
	forn(i, itmp) forn(j, itmp) d[i][j] = dtmp[i][j];
	 
	n = itmp;
	
	return 0;
}

int junta(int nh){
	vi lista;
	//cout << "juntando " << nh << endl;
	forn(i, n){
		if(i==nh) continue;
		if(d[nh][i]==2) lista.pb(i);
	}
	if(lista.empty()) resta(nh);
	else { lista.pb(nh); mergea(nh, lista); }
	
	return 0;
}

int main(){
	while(cin >> n && n){
		init();
		
		forn(i, n) forn(j, n) cin >> d[i][j];
		
		while(n){
			//forn(i, n){ forn(j, n) cout << d[i][j] << ' '; cout << endl; }
			int maxd = 0, nh = -1;
			forsn(j, 1, n){ if(d[0][j]>maxd){ maxd = d[0][j]; nh = j; } }
			junta(nh);
		}
		sort(all(rout));
		forn(i, si(rout)) { cout << rout[i]; if(i<si(rout)-1) cout << " "; }
		cout << endl;				
	}
	return 0;	
}
