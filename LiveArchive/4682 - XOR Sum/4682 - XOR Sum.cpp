#include <iostream>
#include <string>
using namespace std;

/* TRIE */

#define MAXN 131072

int n[MAXN];

struct node {
	node *c[2];
	node(node *left=NULL, node *right=NULL) {
		c[0] = left; c[1] = right;
	}
} *ROOT;

void insert(int v) {
	node *cur = ROOT;
	for (int i=30; i>=0; i--) {
		int bit = (v>>i)&1;
		if (!cur->c[bit]) cur->c[bit] = new node;
		cur = cur->c[bit];
	}
}

int query(int v) {
	int RES = 0; node *cur = ROOT;
	for (int i=30; i>=0; i--) {
		int bit = (v>>i)&1;
		if (cur->c[1-bit]) {
			RES ^= (1<<i);
			cur = cur->c[1-bit];
		} else cur = cur->c[bit];
	}
	return RES;
}

int main() {
	ios::sync_with_stdio(false);
	int T, t, N, i, RES;
	
	cin >> T;
	for (t=0; t<T; t++) {
		cin >> N;
		for (i=1; i<=N; i++) { cin >> n[i]; n[i] ^= n[i-1]; }
		
		RES = 0; ROOT = new node;
		for (i=0; i<N; i++) {
			insert(n[i]);
			RES = max(RES, query(n[i+1]));
		}
		cout << RES << endl;
	}

	return 0;
}
