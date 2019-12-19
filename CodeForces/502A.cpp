#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1024

struct student {
	int score, id;
} n[MAXN];

bool operator <(const student &s1, const student &s2) {
	if (s1.score != s2.score) return s1.score > s2.score;
	else return s1.id < s2.id;
}

int main() {
	int N, A, B, C, D, i;
	
	cin >> N;
	for (i=1; i<=N; i++) {
		cin >> A >> B >> C >> D;
		n[i].score = A+B+C+D;
		n[i].id = i;
	}
	sort(n+1,n+1+N);
	
	for (i=1; i<=N; i++) if (n[i].id == 1) break;
	cout << i << endl;

	return 0;
}
