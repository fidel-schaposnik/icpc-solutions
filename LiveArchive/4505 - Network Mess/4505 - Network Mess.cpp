#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

int main() {

int N, i, a, b, cant, tmp, ib, ia;
char op[8];
bool flag;

cin >> N;

flag = false;
do {

if (flag == true) cout << endl;
else flag = true;

a = b = 0; ia = 1; ib = 2;
for (i=0; i<N; i++) {
   cin >> op;
	cin >> cant;
	if (strcmp(op, "DROP") == 0) {
	   cout << "DROP " << ia << " " << cant << endl;
		a += cant;
	} else if (strcmp(op, "TAKE") == 0) {
		if (b > 0) {
			tmp = MIN(b, cant);
		   cout << "TAKE " << ib << " " << tmp << endl;
			b -= tmp;
			cant -= tmp;
		}
		if (cant > 0) {
			cout << "MOVE " << ia << "->" << ib << " " << a << endl;
			b = a;
			a = 0;
			cout << "TAKE " << ib << " " << cant << endl;
			b -= cant;
		}
	}
}

cin >> N;

} while (N != 0);

return 0;
}
