#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

#define MAXP 512

struct pt {
	int x, y;
} p[2][2*MAXP];

bool operator!=(const pt &p1, const pt &p2) {
	return p1.x != p2.x || p1.y != p2.y;
}

int x[2*MAXP];
map<int, int> v;

void compress(int id, int N) {
	for (int i=0; i<N; i++) x[i]  = p[id][i].x;
	sort(x,x+N); v.clear(); v[x[0]] = 0;
	for (int i=1; i<N; i++) if (x[i] != x[i-1]) v[x[i]] = v[x[i-1]]+1;
	for (int i=0; i<N; i++) p[id][i].x = v[p[id][i].x];
	
	for (int i=0; i<N; i++) x[i]  = p[id][i].y;
	sort(x,x+N); v.clear(); v[x[0]] = 0;
	for (int i=1; i<N; i++) if (x[i] != x[i-1]) v[x[i]] = v[x[i-1]]+1;
	for (int i=0; i<N; i++) p[id][i].y = v[p[id][i].y];
}

int lowerleft(int id, int N) {
	int best = 0;
	for (int i=1; i<N; i++) if (p[id][i].x < p[id][best].x || (p[id][i].x == p[id][best].x && p[id][i].y < p[id][best].y)) best = i;
	return best;
}

void rotate(int id, int N) {
	for (int i=0; i<N; i++) { 
		swap(p[id][i].x, p[id][i].y);
		p[id][i].x *= -1;
	}
}

int main() {
	int N, M, i, j, k;
	
	while (cin >> N) {
		for (i=0; i<N; i++) {
			cin >> p[0][i].x >> p[0][i].y;
			p[0][i+N] = p[0][i];
		}
		compress(0, 2*N);
		
		cin >> M;
		for (i=0; i<M; i++) {
			cin >> p[1][i].x >> p[1][i].y;
			p[1][i+M] = p[1][i];
		}
		compress(1, 2*M);
		
		if (N == M) {
			bool flag = false;
			
			i = lowerleft(0, N); j = lowerleft(1, N);
			for (k=0; k<N; k++) if (p[0][i+k] != p[1][j+k]) break;
			if (k == N) flag = true;
			
			rotate(1, 2*N);
			compress(1, 2*N);
			i = lowerleft(0, N); j = lowerleft(1, N);
			for (k=0; k<N; k++) if (p[0][i+k] != p[1][j+k]) break;
			if (k == N) flag = true;
			
			rotate(1, 2*N);
			compress(1, 2*N);
			i = lowerleft(0, N); j = lowerleft(1, N);
			for (k=0; k<N; k++) if (p[0][i+k] != p[1][j+k]) break;
			if (k == N) flag = true;
			
			rotate(1, 2*N);
			compress(1, 2*N);
			i = lowerleft(0, N); j = lowerleft(1, N);
			for (k=0; k<N; k++) if (p[0][i+k] != p[1][j+k]) break;
			if (k == N) flag = true;
			
			if (flag) cout << "yes" << endl;
			else cout << "no" << endl;
		} else cout << "no" << endl;
	}
	
	return 0;
}
