#include <iostream>
#include <algorithm>
using namespace std;
#define forn(i,n) for(int i = 0; i < (n); i++)
#define forsn(i,m,n) for(int i = (m); i < (n); i++)

typedef long long tint;
#define MAXN 11000

int m,n;
tint call[MAXN][2];

bool inters(tint s1, tint d1, tint s2, tint d2) {
	tint e1 = s1+d1, e2 = s2+d2;
	if (s1>=s2) {
		swap(s1,s2); swap(e1,e2);		
	}	
	if (s2<e1) return true;
	return false;
}

int main() {
	while (cin >> n >> m && n &&  m) {
		forn(i,n) {
			int a,b; cin >> a >> b;
			cin >> call[i][0] >> call[i][1];	
		}
		forn(j,m) {
			tint s,d,res=0;
			cin >> s >> d;
			forn(i,n) if (inters(s,d,call[i][0],call[i][1])) res++;
			cout << res << endl;	
		}
		
	}
	return 0;
}
