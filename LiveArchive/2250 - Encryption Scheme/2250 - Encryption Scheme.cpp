#include <iostream>
#include <cstring>
using namespace std;

char key[129], tar[128];
int lenk, lent;

int issubstr(int start, int end) {
	int i, j, lens;
	bool useful;
	lens = end-start;

	if (lens > lenk) {return -1;}
	for (i=0; i<lenk-lens+1; i++) {
		useful = 1;
		for (j=0; j<lens; j++) {
			if (key[i+j] != tar[start+j]) {useful = 0;}
		}
		if (useful == 1) {return i+1;}
	}
	return -1;
}

int main() {

int start, i, temp, count;

cin >> key;

do {

cin >> tar;

lenk = strlen(key);
lent = strlen(tar);

start = count = 0;
do {
	for (i=lent; i>start; i--) {
		temp = issubstr(start, i);
		if (temp != -1) {
//			cout << temp << ' ' << i-start << endl;
			count++;
			break;
		}
	}
	start = i;
} while (start < lent);

cout << count << endl;

cin >> key;

} while (key[0] != '#' || key[1] != '\0');

return 0;
}
