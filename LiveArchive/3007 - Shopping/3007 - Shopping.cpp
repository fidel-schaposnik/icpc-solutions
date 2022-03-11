#include <iostream>
#include <list>
using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

struct customer {
   int wt;
	int at;
	int ct;
} c[512];

int compare_at(const void *a, const void *b) {
   return (*(customer*)a).at - (*(customer*)b).at;
}

bool compare_ct(int a, int b) {
   return c[a].ct < c[b].ct;
}

int main() {

int C, i, CUR, TIME, ST, RES, k, K;
list<int> q;
list<int>::iterator iter;

cin >> K;

for (k=0; k<K; k++) {

cin >> C;

for (i=0; i<C; i++) {
   cin >> c[i].at;
	cin >> c[i].ct;
	c[i].wt = 0;
}

qsort(c, C, sizeof(customer), compare_at);

CUR = 0; TIME = 0;
while (CUR < C || !q.empty()) {
	if (CUR < C && c[CUR].at == TIME) {
		q.push_back(CUR);
		q.sort(compare_ct);
	   CUR++;
	} else {
	   if (CUR == C) ST = c[q.front()].ct;
		else if (q.empty()) ST = c[CUR].at - TIME;
		else ST = MIN(c[CUR].at - TIME, c[q.front()].ct);

		if (!q.empty()) {
		   c[q.front()].ct -= ST;
			for (iter=q.begin(); iter!=q.end(); iter++) {
				if (iter != q.begin()) c[*iter].wt += ST;
			}
			if (c[q.front()].ct == 0) q.pop_front();
		}
		TIME += ST;
	}
}

RES = 0;
for (i=0; i<C; i++) {
   RES += c[i].wt;
}

cout << C << ' ' << RES << endl;

}

return 0;
}
