#include <iostream>
#include <cstring>
using namespace std;

struct node {
	int limit;
	int edges[100];
	int mintime;
	bool visited;
};

int main() {

int N, M, S, T;
node nodes[100];

int i, tempa, tempb, best;

cin >> N;
cin >> M;
cin >> S; S--;
cin >> T; T--;

do {

for (i=0; i<N; i++) {
	cin >> nodes[i].limit;
	memset(nodes[i].edges, -1, sizeof(nodes[i].edges));
	nodes[i].mintime = -1;
	nodes[i].visited = 0;
}

for (i=0; i<M; i++) {
	cin >> tempa;
	cin >> tempb;
	cin >> nodes[tempa-1].edges[tempb-1];
	nodes[tempb-1].edges[tempa-1] = nodes[tempa-1].edges[tempb-1];
}

nodes[S].mintime = 0;

do {

	best = -1;
	for (i=0; i<N; i++) {
		if (nodes[i].visited == 0 && nodes[i].mintime != -1) {
			if (best == -1) {best = i;}
			else if (nodes[i].mintime < nodes[best].mintime) {best = i;}
		}
	}
	if (best == -1) {
		cout << 0 << endl;
		break;
	} else {
		nodes[best].visited = 1;
	
		if (best == T) {
			cout << nodes[best].mintime << endl;
			break;
		}
	
		for (i=0; i<N; i++) {
			if (nodes[best].edges[i] != -1) {
				if (nodes[i].mintime == -1) {
					if (nodes[i].limit == 0 || nodes[i].limit > nodes[best].mintime + nodes[best].edges[i]) {
						nodes[i].mintime = nodes[best].mintime + nodes[best].edges[i];
					}
				} else if (nodes[i].mintime > nodes[best].mintime + nodes[best].edges[i]) {
						nodes[i].mintime = nodes[best].mintime + nodes[best].edges[i];
				}
			}
		}
	}

} while (1);

cin >> N;
cin >> M;
cin >> S; S--;
cin >> T; T--;

} while (N!=0 || M!=0 || S!=-1 || T!=-1);


return 0;
}
