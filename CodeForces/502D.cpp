#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 12
#define MAXM 1<<MAXN
#define MAXV 128

int m[MAXM], wu[MAXM][MAXM], wu_order[MAXM][MAXM], wu_sum[MAXM][MAXM], CUR, res[MAXM][MAXV];

bool compare(const int &a, const int &b) {
	return wu[CUR][a] < wu[CUR][b];
}

int main() {
	int N, M, Q, n[MAXN], i, j, k, cur, s, e, mid, TOTAL, comp[MAXM];
	char tmp[MAXN+1];
	
	memset(res, -1, sizeof(res));
	
	scanf("%d %d %d", &N, &M, &Q);
	
	TOTAL = 0;
	for (i=0; i<N; i++) {
		scanf("%d", &n[i]);
		TOTAL += n[i];
	}
	
	for (i=0; i<(1<<N); i++) {
		comp[i] = 0;
		for (k=0; k<N; k++) if (i&(1<<k)) comp[i] += n[N-1-k];
	}
	
	for (i=0; i<(1<<N); i++) {
		for (j=0; j<(1<<N); j++) {
			wu[i][j] = TOTAL - comp[i^j];
			wu_order[i][j] = j;
		}
		CUR = i;
		sort(wu_order[i], wu_order[i]+(1<<N), compare);
	}
	
	for (i=0; i<M; i++) {
		scanf("%s", &tmp);
		
		cur = 0;
		for (j=0; j<N; j++) cur = cur*2 + tmp[j]-'0';
		m[cur]++;
	}
	
	for (i=0; i<(1<<N); i++) {
		for (j=0; j<(1<<N); j++) wu_sum[i][j] = m[wu_order[i][j]];
		for (j=1; j<(1<<N); j++) wu_sum[i][j] += wu_sum[i][j-1];
	}
	
	for (i=0; i<Q; i++) {
		scanf("%s %d", &tmp, &k);
		
		cur = 0;
		for (j=0; j<N; j++) cur = cur*2 + tmp[j]-'0';
		
		if (res[cur][k] == -1) {
			if (wu[cur][wu_order[cur][0]] > k) res[cur][k] = 0;
			else {
				s = 0; e = 1<<N;
				while (e-s > 1) {
					mid = (s+e)/2;
					if (wu[cur][wu_order[cur][mid]] <= k) s = mid;
					else e = mid;
				}
				res[cur][k] = wu_sum[cur][s];
			}
		}
		printf("%d\n", res[cur][k]);
	}

	return 0;
}
