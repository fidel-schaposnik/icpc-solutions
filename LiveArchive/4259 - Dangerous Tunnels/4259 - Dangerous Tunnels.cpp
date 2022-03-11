#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a) : (b) )
#define MAX(a,b) ( (a)>(b) ? (a) : (b) )

#define MAXN 512
#define INF 256

int K, AA[MAXN][MAXN], F[MAXN][MAXN], N;

struct edge {
   int a, b, w;
} e[32768];

struct node {
   int best, prev;
	vector<int> c;
} n[MAXN];

int cmp(const void *a, const void *b) {
   return (*(edge*)a).w - (*(edge*)b).w;
}

int edmondskarp(int **A, int SOURCE, int SINK) {
   int s[MAXN], S, E, FLOW, tmp, it;
	bool v[MAXN];

	memset(F, 0, sizeof(F));
	FLOW = 0;
	while (1) {
	   memset(v, false, sizeof(v));
		n[SOURCE].best = INF;
		n[SOURCE].prev = -1;
		s[0] = SOURCE; S = 0; E = 1; v[SOURCE] = true;
		while (S != E && s[S] != SINK) {
		   for (it=0; it<n[s[S]].c.size(); it++) {
				tmp = n[s[S]].c[it];
				if (v[tmp]==false && A[s[S]][tmp]-F[s[S]][tmp]>0) {
			   	v[tmp] = true;
					n[tmp].prev = s[S];
					n[tmp].best = MIN(n[s[S]].best, A[s[S]][tmp] - F[s[S]][tmp]);
					s[E] = tmp;
					E++;
				}
			}
			S++;
		}
		if (S==E) return FLOW;
		else {
		   FLOW += n[SINK].best;
			tmp = SINK;
			while (n[tmp].prev != -1) {
				F[n[tmp].prev][tmp] += n[SINK].best;
				F[tmp][n[tmp].prev] = - F[n[tmp].prev][tmp];
				tmp = n[tmp].prev;
			}
		}
	}
}


bool check(int E) {
	int *A[MAXN], i;

//	cout << "probando con las aristas [0, " << E << ")" << endl;

   memset(AA, 0, sizeof(AA));
	for (i=0; i<MAXN; i++) A[i] = AA[i];

	for (i=0; i<2*N+2; i++) n[i].c.clear();

	for (i=1; i<=N; i++) {
		AA[i][i+N+1] /*= AA[i+N+1][i]*/ = 1;//?
		n[i].c.push_back(i+N+1);
		n[i+N+1].c.push_back(i);
	}

	for (i=0; i<E; i++) {
		if (e[i].a == 0) {
			/*AA[e[i].b][0] = */ AA[0][e[i].b] = 1;//?
			n[0].c.push_back(e[i].b);
			n[e[i].b].c.push_back(0);
		} else {
			/* AA[e[i].b][e[i].a+N+1]  = */ AA[e[i].a+N+1][e[i].b] = 1;//?
			n[e[i].a+N+1].c.push_back(e[i].b);
			n[e[i].b].c.push_back(e[i].a+N+1);
		}
	}

/*	for (i=0; i<2*N+2; i++) {
	   cout << "el nodo " << i << " esta conectado con";
		for (int j=0; j<n[i].c.size(); j++) cout << ' ' << n[i].c[j];
		cout << endl;
	}

	cout << edmondskarp(A, 0, N+1) << ' ' << K << endl << endl;*/

	if (edmondskarp(A, 0, N+1) < K) return false;
	else return true;
}

int main() {

	int E, i, tmp1, tmp2, l, r, m, T;
	cin >> N;
	T = 1;

	do {
		cin >> E;

		for (i=0; i<E; i++) {
		   cin >> tmp1;
			cin >> tmp2;
			cin >> e[i].w;
			e[i].a = MIN(tmp1, tmp2);
			e[i].b = MAX(tmp1, tmp2);
		}

		qsort(e, E, sizeof(edge), cmp);

		/*for (i=0; i<E; i++) {
			cout << "arista de " << e[i].a << " a " << e[i].b << " con peligrosidad " << e[i].w << endl;
		}
		cout << endl;*/

		cin >> K;

		cout << "Case " << T++ << ": ";
		if (check(E) == false) cout << "no solution" << endl;
		else {
		   l = 0; r = E;
		   while (l+1 < r) {
			  m = (l+r)/2;
			if (check(m) == true) r = m;
			   else l = m;
		   }
		   cout << e[l].w << endl;
		}

		cin >> N;
	} while (N!=0);

	return 0;
}
