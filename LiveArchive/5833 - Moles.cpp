#include <cstdio>
#include <map>
#include <iostream>
using namespace std;

#define MAXN 1048576
#define MAXS 2097152
#define MAXP 8192

typedef unsigned long long HASH;

#define VALUE(c) ( (c)=='0' ? 3ULL : 5ULL )

struct node {
	int v, l, r, s;
} n[MAXN];

int S, stack[MAXN];
char s[MAXS], p[MAXP];
HASH h[MAXS], pow;

void fill(int cur) {
	int STACK = 0;
	
	stack[STACK++] = cur;
	while (STACK) {
		cur = stack[STACK-1];
		s[S++] = (n[cur].v)%2+'0';
		if (n[cur].s == -1) {
			n[cur].s++;
			if (n[cur].l != -1) { stack[STACK++] = n[cur].l; continue; }
		}
		if (n[cur].s == 0) {
			n[cur].s++;
			if (n[cur].r != -1) { stack[STACK++] = n[cur].r; continue; }
		}
		if (n[cur].s == 1) STACK--;
	}
}

HASH calc_hash(int s, int e) {
	return h[e]-h[s]*pow;
}

map<int, int> m;

int main() {
	int T, t, N, i, tmp, P, RES;
	map<int,int>::iterator prev, next;
	HASH phash;
	
	scanf("%d", &T);
	for (t=1; t<=T; t++) {
		scanf("%d", &N);
		
		m.clear(); m[0] = m[N+1] = -1;
		for (i=0; i<N; i++) n[i].v = n[i].l = n[i].r = n[i].s = -1;
		
		scanf("%d", &tmp); n[0].v = tmp; m[tmp] = 0;
		for (i=1; i<N; i++) {
			scanf("%d", &tmp);
			prev = next = m.lower_bound(tmp); prev--;
			if (prev->second > next->second) n[prev->second].r = i;
			else n[next->second].l = i;
			n[i].v = tmp; m[tmp] = i;
		}
		
		scanf("%s", &p); phash = 0ULL; pow = 1ULL;
		for (P=0; p[P]!='\0'; P++) {
			phash = phash*33ULL + VALUE(p[P]);
			pow = pow*33ULL;
		}
		
		S = 0; fill(0); s[S] = '\0';
		
		h[0] = 0;
		for (i=0; i<S; i++) h[i+1] = h[i]*33ULL + VALUE(s[i]);
		
		RES = 0;
		for (i=0; i+P<=S; i++) if (calc_hash(i,i+P) == phash) RES++;
		printf("Case #%d: %d\n", t, RES);
	}

	return 0;
}
