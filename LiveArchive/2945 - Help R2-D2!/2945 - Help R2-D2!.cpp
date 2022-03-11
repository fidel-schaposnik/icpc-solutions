#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 1048576

int A[MAXN], RMQ[2*MAXN], N;

#define LEFT(n) ( 2*(n) )
#define RIGHT(n) ( 2*(n)+1 )

void rmq_init(int n, int s, int e, int *m, int *rmq) {
   if (s+1 == e) rmq[n] = s;
	else {
	   rmq_init(LEFT(n), s, (s+e)/2, m, rmq);
		rmq_init(RIGHT(n), (s+e)/2, e, m, rmq);
		if (m[rmq[LEFT(n)]] > m[rmq[RIGHT(n)]]) rmq[n] = rmq[LEFT(n)];
		else rmq[n] = rmq[RIGHT(n)];
	}
}

int rmq_query(int n, int s, int e, int *m, int *rmq, int a, int b) {
   if (a > e || b < s) return -1;
	else if (s >= a && e <= b) return rmq[n];
	else {
	   int l = rmq_query(LEFT(n), s, (s+e)/2, m, rmq, a, b);
		int r = rmq_query(RIGHT(n), (s+e)/2, e, m, rmq, a, b);
		if (l == -1 || m[r] > m[l]) return r;
		else return l;
	}
}

void rmq_update(int n, int s, int e, int *m, int *rmq, int p) {
   if (s+1 == e) rmq[n] = s;
	else {
	   if (p < (s+e)/2) rmq_update(LEFT(n), s, (s+e)/2, m, rmq, p);
		else rmq_update(RIGHT(n), (s+e)/2, e, m, rmq, p);
		if (m[rmq[LEFT(n)]] > m[rmq[RIGHT(n)]]) rmq[n] = rmq[LEFT(n)];
		else rmq[n] = rmq[RIGHT(n)];
	}
}

void add(int v) {
   int s, e, n;

	n = 1; s = 0; e = N;
	while (s+1 < e) {
		if (A[RMQ[LEFT(n)]] >= v) {e = (s+e)/2; n = LEFT(n);}
		else {s = (s+e)/2; n = RIGHT(n);}
	}
	A[s] -= v; rmq_update(1, 0, N, A, RMQ, s);
}

int main() {

int K, NN, R, cur, i, RES;
char tmp[8];
bool flag;

flag = false;
while (scanf("%d %d", &K, &N) != EOF) {
if (flag == false) flag = true;
else printf("\n");

for (i=0; i<N; i++) A[i] = K;

rmq_init(1, 0, N, A, RMQ);

NN = N;
while (NN > 0) {
   scanf("%s", tmp);
	if (strcmp(tmp, "b") == 0) {
	   scanf("%d %d", &R, &cur);
		for (i=0; i<R; i++) add(cur);
		NN -= R;
	} else {
      sscanf(tmp, "%d", &cur);
		add(cur);
		NN--;
	}
}

RES = 0;
for (i=0; i<N && A[i]!=K; i++) RES += A[i];
printf("%d %d\n", i, RES);

}

return 0;
}
