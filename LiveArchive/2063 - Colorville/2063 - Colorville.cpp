#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {

int p[4], P, B, C, cur, i;
char b[128], tmp[4];

while (scanf("%d %d %d", &P, &B, &C) != EOF && P!=0) {

for (i=0; i<P; i++) p[i] = 0;

cin >> b;

for (i=B-1; i>=0; i--) b[i+1] = b[i];
b[0] = ' '; b[B+1] = '\0';

cur = 0;
for (i=0; i<C; i++) {
   cin >> tmp;
//	cout << "Player " << cur+1 << " draws " << tmp;
	while (p[cur] != B) {
		p[cur]++;
	   if (b[p[cur]] == tmp[0])  {
		   if (strlen(tmp) == 2) tmp[1] = '\0';
			else break;
		}
	}
//	cout << ",  moves to square " << p[cur] << endl;
	if (p[cur] == B) break;
	cur++;
	if (cur == P) cur = 0;
}

if (p[cur] == B) cout << "Player " << cur+1 << " won after " << i+1 << " cards." << endl;
else cout << "No player won after " << C << " cards." << endl;

i++;
while (i<C) {cin >> tmp; i++;}

}

return 0;
}
