#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <queue>

using namespace std;

typedef vector<int> vi;

#define forn(i,n) for(int i = 0; i < (n); ++i)
#define forsn(i,m,n) for(int i = (m); i < (n); ++i)
#define si(a) (int)(a.size())
#define pb push_back
#define mp make_pair
#define all(x) x.begin(),x.end()

#define _ALTA {forn(h,6) rot[p][h] = d[h]; p++;}
#define _DER forn(h,6) d[h] = _der[d[h]];
#define _UP forn(h,6) d[h] = _up[d[h]];

int rot[24][6];
const int _der[6] = {0, 2, 4, 1, 3, 5};
const int _up[6] = {1, 5, 2, 3, 0, 4};
const int x[6] = {2, 1, 0, 5, 4, 3};

void rotaciones() {
	int d[6], p=0;
	forn(i,6) d[i] = i;
	forn(i,2) {
		forn(j,3) {
			_ALTA; _DER;
			_ALTA; _DER;
			_ALTA; _DER;
			_ALTA; _UP;	
		}	
		_DER; _UP; _UP;
	}	
	return;
}

int n, cubo[4][6],r, res, tmp[4][6];
map<string,int> m;

void print() {
	forn(i,n) {
		forn(h,6) cout << tmp[i][h] <<" ";
		cout << endl;	
	}	
	cout << endl;
}

void dfs(int lev) {
	if (lev==n-1) {		
		int ans = 0;
		forn(h,6) {
			int d[4];
			forn(i,n) d[i] = tmp[i][h];
			sort(d,d+n);
			int maxrep = 0;
			forn(i,n) {
				int act = d[i], cant = 0;
				while(d[i]==act && i<n)	{
					cant++; i++;		
				}
				i--;
				maxrep = max(maxrep, cant);
			}
			ans+= n-maxrep;	
		}	
		if (res == -1 || ans<res) {res = ans;}//	print(); }
		return;
	} else {
		forn(k,24) {
			forn(h,6) {
				tmp[lev+1][rot[k][h]] = cubo[lev+1][h];
			}
			dfs(lev+1);	
		}	
	}
}

void init(){
	r = 0; 
	m.clear();
	res = -1;
}

int main(){
	rotaciones();
/*	forn(k,24) {
		forn(h,6) cout << rot[k][h] <<" ";
		cout << endl;	
	}	
	cout << endl;
	return 0;*/
	
	while(cin >> n && n){
		init();
		forn(i,n) forn(j,6) {
			string s; cin >> s;
			if (m.count(s)==0) m[s] = r++;
			cubo[i][x[j]] = m[s];	
		}		
		forn(h,6) tmp[0][h] = cubo[0][h];
		dfs(0);
		cout << res << endl;
	}
	return 0;	
}
