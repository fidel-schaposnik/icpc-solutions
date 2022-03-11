#include <iostream>
using namespace std;

struct child {
	char name[15];
	int volume;
};

int main() {

int N, i, j, a, b, c;
child childs[101];

int volumes[3][2];
int count, min, max;
bool add;

cin >> N;

do {

for (i=0; i<N; i++) {
	cin >> childs[i].name;
	cin >> a;
	cin >> b;
	cin >> c;
	childs[i].volume = a*b*c;
}

for (j=0; j<3; j++) {
	volumes[j][0] = -1;
}

count = 0;
for (i=0; i<N; i++) {
	add = 1;
	for (j=0; j<count; j++) {
		if (volumes[j][0] == childs[i].volume) {
			volumes[j][1]++;
			add = 0;
			break;
		}
	}
	if (add == 1) {
		volumes[count][0] = childs[i].volume;
		volumes[count][1] = 1;
		count++;
	}
}

if (count == 1) {
	cout << "No child has lost jelly." << endl;
} else if (count == 2) {
	if (childs[0].volume < childs[1].volume) {
		cout << childs[0].name << " has lost jelly to " << childs[1].name << "." << endl;
	} else {
		cout << childs[1].name << " has lost jelly to " << childs[0].name << "." << endl;
	}
} else {

max = 0;
for (i=1; i<3; i++) {
	if (volumes[i][1] > volumes[max][1]) {
		max = i;
	}
}

a = b = -1;
for (i=0; i<N; i++) {
	if (childs[i].volume < volumes[max][0]) {a = i;}
	else if (childs[i].volume > volumes[max][0]) {b = i;}
}

cout << childs[a].name << " has lost jelly to " << childs[b].name << "." << endl;

}

cin >> N;

} while (N!=0);

return 0;
}
