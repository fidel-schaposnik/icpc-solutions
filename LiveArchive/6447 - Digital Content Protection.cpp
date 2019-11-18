#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

vector<unsigned long long> RES;
set<unsigned long long> r;

void calc(unsigned long long n, unsigned long long s, unsigned long long e) {
	set<unsigned long long>::iterator tmp = r.lower_bound(s);
	if (tmp == r.end() || *tmp >= e ) RES.push_back(n);
	else if (e-s > 1ULL) {
		calc(2ULL*n, s, (s+e)/2ULL);
		calc(2ULL*n+1ULL, (s+e)/2ULL, e);
	}
}

int main() {
	int N, R, i;
	unsigned long long tmp;
	
	while (cin >> N >> R) {
		r.clear();
		for (i=0; i<R; i++) { cin >> tmp; r.insert(tmp); }
		
		RES.clear();
		calc(1ULL, 1ULL<<N, 1ULL<<(N+1));
		
		sort(RES.begin(), RES.end());
		cout << RES[0];
		for (i=1; i<(int)RES.size(); i++) cout << ' ' << RES[i];
		cout << endl;
	}

	return 0;
}
