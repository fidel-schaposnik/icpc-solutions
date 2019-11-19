#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define MAXN 2048

struct node {
	bool v;
	int k;
	vector<int> c;
} n[MAXN];

set< pair<int, int> > s;

int main() {
	int T, t, N, K, E, A, B, i, cur, next;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N >> K >> E;
		for (i=1; i<=N; i++) {
			n[i].c.clear();
			n[i].v = true;
			n[i].k = 0;
		}
		
		for (i=0; i<E; i++) {
			cin >> A >> B;
			n[A].c.push_back(B); n[A].k++;
			n[B].c.push_back(A); n[B].k++;
		}
		
		s.clear();
		for (i=1; i<=N; i++) s.insert(make_pair(n[i].k, i));
		
		while (!s.empty()) {
			cur = s.begin()->second;
			if (n[cur].k >= K) break;
			
			s.erase(s.begin()); n[cur].v = false;
			for (i=0; i<n[cur].c.size(); i++) {
				next = n[cur].c[i];
				if (!n[next].v) continue;
				
				s.erase(make_pair(n[next].k, next));
				n[next].k--;
				s.insert(make_pair(n[next].k, next));
			}
		}
		cout << s.size() << endl;
	}

	return 0;
}
