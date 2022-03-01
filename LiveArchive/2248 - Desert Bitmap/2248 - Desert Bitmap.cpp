#include <iostream>
using namespace std;

int ro, co, rm, cm;
bool ed[16][16], map[100][100];

bool testpos(int x, int y) {
	int i, j;
	for (i=0; i<ro; i++) {
		for (j=0; j<co; j++) {
			if (map[y+i][x+j] == 0 && ed[i][j] == 1) {
				return 0;
			}
		}
	}
	return 1;
}

int main() {

int i, j, result;
char t;

cin >> ro;
cin >> co;

do {

for (i=0; i<ro; i++) {
	for (j=0; j<co; j++) {
		cin >> t;
		if (t == '#') {ed[i][j] = 1;}
		else {ed[i][j] = 0;}
	}
}

cin >> rm;
cin >> cm;

for (i=0; i<rm; i++) {
	for (j=0; j<cm; j++) {
		cin >> t;
		if (t == '#') {map[i][j] = 1;}
		else {map[i][j] = 0;}
	}
}

result = 0;
for (i=0; i<cm-co+1; i++) {
	for (j=0; j<rm-ro+1; j++) {
		result += testpos(i, j);
	}
}
cout << result << endl;

cin >> ro;
cin >> co;

} while (ro != 0 || co != 0);

return 0;
}
