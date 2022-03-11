#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

#define ABS(x) ( (x)<0 ? -(x) : (x) )

string invert(string s) {
	string res = "";
   for (int i=s.size()-1; i>=0; i--) {
	   if (s[i] >= 'a' && s[i] <= 'z') res += s[i]-'a'+'A';
		else if (s[i] >= 'A' && s[i] <= 'Z') res += s[i]-'A'+'a';
	}
	return res;
}

int main() {

srand(time(0));

int i, N, a, l, tmp;
string n, s1, s2, s3, s4;

cin >> n;

do {

a = l = 0;
while (n.size() > 0) {
	N = n.size();

   for (i=1; i<N; i++) {
	   if (ABS(n[i]-n[i-1]) == 32) {
			n = n.substr(0, i-1) + n.substr(i+1, N-i-1);
		   break;
		} else if (ABS(n[i]-n[i-1]) == 0) {
			n = n.substr(0, i-1) + n.substr(i+1, N-i-1);
			a++;
		   break;
		}
	}
	if (i == N) {
		if (n[0] == n[N-1]) {
			n = n.substr(1, N-2);
			a++;
			continue;
		} else if (ABS(n[0]-n[N-1]) == 32) {
			n = n.substr(1, N-2);
			continue;
		}
	} else continue;

	for (i=3; i<N; i++) {
	   if (ABS(n[i]-n[i-2]) == 32 && ABS(n[i-1]-n[i-3]) == 32) {
			n = n.substr(0, i-3) + n.substr(i+1, N-i-1);
			l++;
			break;
		}
	}
	if (i == N) {
	   if (N>4 && ABS(n[2]-n[0]) == 32 && ABS(n[1]-n[N-1]) == 32) {
			n = n.substr(3, N-4);
			l++;
			continue;
		} else if (N>4 && ABS(n[1]-n[N-1]) == 32 && ABS(n[0]-n[N-2]) == 32) {
			n = n.substr(2, N-4);
			l++;
			continue;
		} else if (N>4 && ABS(n[0]-n[N-2]) == 32 && ABS(n[N-1]-n[N-3]) == 32) {
			n = n.substr(1, N-4);
			l++;
			continue;
		}
	} else continue;

	tmp = rand()%N;
	n = n.substr(tmp, N-tmp) + n.substr(0, tmp);
	for (i=1; i<N; i++) {
	   if (n[i] == n[0] || ABS(n[i]-n[0]) == 32) break;
	}

	tmp = rand()%(i-1);
	s2 = n.substr(1, tmp);
	s3 = n.substr(tmp+1, i-1-tmp);

	tmp = rand()%(N-i-1);
	s4 = n.substr(i+1, tmp);
	s1 = n.substr(i+1+tmp, N-i-1-tmp);

	if (n[0] == n[i]) {
	   n = s2 + n[0] + s1 + invert(s3) + n[0] + invert(s4);
	} else {
		n = s2 + n[0] + s1 + s4 + n[i] + s3;
	}
}

if (a > 0) a += 2*l;

if (a == 1) cout << "1 arm" << endl;
else if (a > 1) cout << a << " arms" << endl;
else if (l == 1) cout << "1 leg" << endl;
else if (l > 1) cout << l << " legs" << endl;
else cout << "none" << endl;

cin >> n;

} while (n!="END");

return 0;
}
