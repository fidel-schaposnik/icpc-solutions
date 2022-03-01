#include <iostream>
#include <cstdio>
using namespace std;

#define READ0(c) ( (c)=='D' ? 1 : ( (c)=='O' ? 2 : 3 ) )
#define READ2(c) ( (c)=='R' ? 1 : ( (c)=='G' ? 2 : 3 ) )
#define READ3(c) ( (c)=='O' ? 1 : ( (c)=='F' ? 2 : 3 ) )

struct card {
   int v[4];
	char name[8];
} c[12];

bool isvalidP(int A, int B, int C, int P) {
   return ( c[A].v[P] == c[B].v[P] && c[B].v[P] == c[C].v[P] ) || ( c[A].v[P] != c[B].v[P] && c[B].v[P] != c[C].v[P] && c[A].v[P] != c[C].v[P] );
}

bool isvalid(int A, int B, int C) {
   for (int i=0; i<4; i++) {
	   if (isvalidP(A, B, C, i) == false) return false;
	}
	return true;
}

int main() {

int i, j, k, C, K;

K = 1;

while (1) {

for (i=0; i<12; i++) {
   if (scanf("%s", c[i].name) == EOF) break;
	c[i].v[0] = READ0(c[i].name[0]);
	c[i].v[1] = c[i].name[1]-'0';
	c[i].v[2] = READ2(c[i].name[2]);
	c[i].v[3] = READ3(c[i].name[3]);
}
if (i == 0) break;

cout << "CARDS: ";
for (i=0; i<12; i++) {
	cout << ' ' << c[i].name;
}
cout << endl;

C = 1;
for (i=0; i<12; i++) {
   for (j=i+1; j<12; j++) {
      for (k=j+1; k<12; k++) {
		   if (isvalid(i, j, k) == true) {
				if (C == 1) cout << "SETS:   ";
				else cout << "        ";
			   cout << C << ".  " << c[i].name << ' ' << c[j].name << ' ' << c[k].name << endl;
				C++;
			}
		}
	}
}
if (C == 1) cout << "SETS:   *** None Found ***" << endl;

cout << endl;

}

return 0;
}
