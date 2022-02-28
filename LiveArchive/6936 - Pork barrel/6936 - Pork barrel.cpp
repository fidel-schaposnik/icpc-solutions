#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

/* Persistent segment tree */

#define MAXM 131072
#define MAXN 1024
#define MAXT 10000000

#define OTHER(id,x) ( m[(id)].a == (x) ? m[(id)].b : m[(id)].a )

struct edge {
	int a, b, w;
} m[MAXM];

bool operator<(const edge &e1, const edge &e2) {
	if (e1.w != e2.w) return e1.w > e2.w;
	else if (e1.a != e2.a) return e1.a < e2.a;
	else return e1.b < e2.b;
}

set<int> adj[MAXN];
int v[MAXN], s[MAXN];

int bfs(int start, int end) {
	int S, E, i, cur, next;
	
	memset(v, -1, sizeof(v)); v[start] = -2;
	S = E = 0; s[E++] = start;
	while (S < E) {
		cur = s[S++];
		if (cur == end) break;

		for (set<int>::iterator it=adj[cur].begin(); it!=adj[cur].end(); it++) {
			next = OTHER(*it, cur);
			if (v[next] == -1) {
				if (v[cur] == -2 || m[v[cur]].w < m[*it].w) v[next] = *it;
				else v[next] = v[cur];
				s[E++] = next;
			}
		}
	}
	return v[end];
}

int f[MAXN];

int getf(int cur) {
	if (f[cur] != cur) f[cur] = getf(f[cur]);
	return f[cur];
}

int NODES = 0;

struct tree_node {
	int l, r, v;
} tree[MAXT];

void init(int cur, int s, int e) {
	tree[cur].v = 0;
	if (e-s > 1) {
		tree[cur].l = NODES++; init(tree[cur].l, s, (s+e)/2);
		tree[cur].r = NODES++; init(tree[cur].r, (s+e)/2, e);
	}
}

void update(int cur, int s, int e, int ref, int p, int v) {
	tree[cur].v = tree[ref].v+v;
	if (e-s > 1) {
		int m = (s+e)/2;
		if (p < m) {
			tree[cur].l = NODES++;
			tree[cur].r = tree[ref].r;
			update(tree[cur].l, s, m, tree[ref].l, p, v);
		} else {
			tree[cur].l = tree[ref].l;
			tree[cur].r = NODES++;
			update(tree[cur].r, m, e, tree[ref].r, p, v);
		}
	}
}

int query(int cur, int s, int e, int a, int b) {
	if (s >= b || e <= a) return 0;
	else if (s >= a && e <= b) return tree[cur].v;
	else return query(tree[cur].l, s, (s+e)/2, a, b) + query(tree[cur].r, (s+e)/2, e, a, b);
}

//void print(int cur, int s, int e) {
//	if (e-s == 1) cerr << tree[cur].v << ' ';
//	else { print(tree[cur].l, s, (s+e)/2); print(tree[cur].r, (s+e)/2, e); }
//}

int main() {
	int T, t, N, M, Q, L, H, i, tmp, fa, fb, root, s, e, mid, RES;
	
	scanf("%d", &T);
	for (t=0; t<T; t++) {
		scanf("%d %d", &N, &M);
		for (i=0; i<M; i++) scanf("%d %d %d", &m[i].a, &m[i].b, &m[i].w);
		sort(m,m+M);
		
		NODES = M+1;
		init(0, 0, M);
		
		for (i=1; i<=N; i++) f[i] = i;
		for (i=0; i<M; i++) {
			fa = getf(m[i].a); fb = getf(m[i].b);
			if (fa == fb) {
				tmp = bfs(m[i].a, m[i].b);
				adj[m[tmp].a].erase(tmp);
				adj[m[tmp].b].erase(tmp);
				
				root = NODES++;
				update(root, 0, M, i, tmp, -m[tmp].w);
			} else { f[fa] = fb; root = i; }
			
			adj[m[i].a].insert(i);
			adj[m[i].b].insert(i);
			update(i+1, 0, M, root, i, m[i].w);
		}
		
		scanf("%d", &Q); RES = 0;
		for (i=0; i<Q; i++) {
			scanf("%d %d", &L, &H);
			L -= RES; H -= RES;
			
			s = 0; e = M;
			while (e-s > 1) {
				mid = (s+e)/2;
				if (m[mid].w < L) e = mid;
				else s = mid;
			}
			tmp = e;
			
			s = 0; e = M;
			while (e-s > 1) {
				mid = (s+e)/2;
				if (m[mid].w <= H) e = mid;
				else s = mid;
			}
			
			RES = query(tmp, 0, M, (m[s].w <= H ? s : e), M);
			printf("%d\n", RES);
		}
	}

	return 0;
}
