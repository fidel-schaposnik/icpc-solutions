#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 65536
#define LOGMAXN 17
#define ALF 256

int m[MAXN], prm[MAXN], g[MAXN], gg[MAXN], lcp[MAXN], c[ALF], p[ALF], DIST, N, st_lcp[LOGMAXN][MAXN], st_m[LOGMAXN][MAXN];
char a[MAXN];

void st_init_min(int *mm, int NN, int **st) {
   int i, j;

   for (i=0; i<NN; i++) st[0][i] = i;
	for (j=1; (1<<j)<=NN; j++) {
	   for (i=0; i+(1<<j)<=NN; i++) {
		   if (mm[st[j-1][i]] < mm[st[j-1][i+(1<<(j-1))]]) st[j][i] = st[j-1][i];
			else st[j][i] = st[j-1][i+(1<<(j-1))];
		}
	}

}

void st_init_max(int *mm, int NN, int **st) {
   int i, j;

   for (i=0; i<NN; i++) st[0][i] = i;
	for (j=1; (1<<j)<=NN; j++) {
	   for (i=0; i+(1<<j)<=NN; i++) {
		   if (mm[st[j-1][i]] > mm[st[j-1][i+(1<<(j-1))]]) st[j][i] = st[j-1][i];
			else st[j][i] = st[j-1][i+(1<<(j-1))];
		}
	}
}

unsigned int clz(int n) {
   for (int i=31; i>=0; i--) if ((n>>i)==1) return 31-i;
	return 32;
}

int st_query_min(int *mm, int NN, int **st, int s, int e) {
   int k = 31 - clz(e-s);
	if (mm[st[k][s]] < mm[st[k][e-(1<<k)]]) return st[k][s];
	else return st[k][e-(1<<k)];
}

int st_query_max(int *mm, int NN, int **st, int s, int e) {
   int k = 31 - clz(e-s);
	if (mm[st[k][s]] > mm[st[k][e-(1<<k)]]) return st[k][s];
	else return st[k][e-(1<<k)];
}

int compare(const void *a, const void *b) {
   int da=*(int*)a + DIST, db=*(int*)b + DIST;
	if (da<N && db<N) return prm[da]- prm[db];
	else if (da<N) return 1;
	else if (db<N) return -1;
	else return db-da;
}

int main() {

int M, i, j, s, e, h, *lcp_st[LOGMAXN], *m_st[LOGMAXN], BESTL, BESTPOS, tmp;

for (i=0; i<LOGMAXN; i++) {
   lcp_st[i] = st_lcp[i];
   m_st[i] = st_m[i];
}

cin >> M;

do {

cin >> a;
N = strlen(a);

if (M == 1) {
   cout << N << ' ' << 0 << endl;
} else {

memset(c, 0, sizeof(c));
for (i=0; i<N; i++) c[a[i]]++;

p[0] = 0;
for (i=1; i<ALF; i++) p[i] = p[i-1]+c[i-1];

memcpy(c, p, sizeof(p));
for (i=0; i<N; i++) {
   m[p[a[i]]] = i;
	prm[i] = p[a[i]];
   g[p[a[i]]] = c[a[i]];
	p[a[i]]++;
}
g[N] = N;

for (i=1; i<N; i<<=1) {
   s = e = 0;
	while (e <= N) {
	   if (g[s] == g[e]) e++;
		else {
			DIST = i;
			qsort(m+s, e-s, sizeof(int), compare);
			gg[s] = s;
			for (j=s+1; j<e; j++) {
			   if (m[j]+i < N && m[j-1]+i < N && g[prm[m[j]+i]] == g[prm[m[j-1]+i]]) {
				   gg[j] = gg[j-1];
				} else gg[j] = j;
			}
			s = e;
		}
	}
	memcpy(g, gg, sizeof(gg));
	for (j=0; j<N; j++) prm[m[j]] = j;
}

h = lcp[0] = 0;
for (i=0; i<N; i++) {
   if (prm[i] > 0) {
      j = m[prm[i]-1];
      while (i+h < N && j+h < N && a[i+h] == a[j+h]) h++;
	   lcp[prm[i]] = h;
   	if (h > 0) h--;
	}
}

st_init_min(lcp, N, lcp_st);
st_init_max(m, N, m_st);

BESTL = 0; BESTPOS = -1;
for (i=1; i+M-1<=N; i++) {
	if (lcp[st_query_min(lcp, N, lcp_st, i, i+M-1)] > BESTL || (lcp[st_query_min(lcp, N, lcp_st, i, i+M-1)] == BESTL && m[st_query_max(m, N, m_st, i-1, i+M-1)] > BESTPOS)) {
	   BESTL = lcp[st_query_min(lcp, N, lcp_st, i, i+M-1)];
		BESTPOS = m[st_query_max(m, N, m_st, i-1, i+M-1)];
	}
}

if (BESTL == 0) cout << "none" << endl;
else cout << BESTL << " " << BESTPOS << endl;

}

cin >> M;

} while (M != 0);

return 0;
}
