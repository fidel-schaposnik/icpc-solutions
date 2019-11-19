#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 15
#define INF 1000000000

int d[1<<MAXN], s[1<<MAXN], N;

void print(int cur) {
	for (int i=0; i<N; i++) cout << ((cur>>i)&1); cout << endl;
}

int main() {
	int M, tmp, i, j, k, START, END1, END2, S, E, cur;
	
	while (cin >> N >> M) {
		START = 0;
		for (i=0; i<N; i++) {
			cin >> tmp;
			START ^= (tmp<<i);
		}

		END1 = END2 = k = 0;
		for (i=0; i<M; i++) {
			cin >> tmp;
			for (j=0; j<tmp; j++) {
				END1 ^= ((i&1)<<k);
				END2 ^= (((i&1)^1)<<k);
				k++;
			}
		}
		
		for (i=0; i<(1<<N); i++) d[i] = INF; S = E = 0;
		d[START] = 0; s[E++] = START;
		while (S < E) {
			cur = s[S++];
			for (i=0; i<N-1; i++) if (((cur>>i)&1) != ((cur>>(i+1))&1) && d[cur^(1<<i)^(1<<(i+1))] == INF) {
				d[cur^(1<<i)^(1<<(i+1))] = d[cur]+1;
				s[E++] = cur^(1<<i)^(1<<(i+1));
			}
		}
		cout << min(d[END1], d[END2]) << endl;
	}

	return 0;
}
