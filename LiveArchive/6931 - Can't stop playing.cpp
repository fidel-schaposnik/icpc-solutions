#include <iostream>
#include <map>
using namespace std;

#define MAXS 16384
#define INF 1000000000

map< int, pair<int,char> > s[MAXS];

int low(int n) {
	if (!n) return INF;
	for (int i=1; ; i*=2) if (i&n) return i;
}

int high(int n) {
	for (int i=1; ; i*=2) if (n<i) return i/2;
}

void print(int level, int value) {
	if (level) {
		print(level-1, s[level][value].first);
		cout << s[level][value].second;
	}
}

int state(int a, int b) {
	int ha = high(a), hb = high(b);
	if (ha <= hb) return a+hb;
	else return a;
}

int main() {
	int T, t, N, i, tmp, left, right, TOT;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N; TOT = 0;
		
		s[0].clear(); s[0][0] = make_pair(-1,'x');
		for (i=1; i<=N; i++) {
			cin >> tmp;
			
			s[i].clear();
			for (map< int, pair<int,char> >::iterator it=s[i-1].begin(); it!=s[i-1].end(); it++) {
				left = it->first; right = TOT-left;
				if (low(left) >= tmp) s[i][state(left+tmp,right)] = make_pair(left,'l');
				if (low(right) >= tmp) s[i][state(left,right+tmp)] = make_pair(left,'r');
			}
			TOT += tmp;
		}
		
		if (low(TOT) == TOT && s[N].find(TOT) != s[N].end()) { print(N, TOT); cout << endl; }
		else cout << "no" << endl;
	}

	return 0;
}
