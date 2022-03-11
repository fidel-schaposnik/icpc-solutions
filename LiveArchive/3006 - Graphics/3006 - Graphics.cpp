#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

bool good;

void up(char str[], int length) {
	if (length == 0) {good = 0;}
	if (str[length-1] == '3') {
		str[length-1] = '2';
	} else if (str[length-1] == '4') {
		str[length-1] = '1';
	} else if (str[length-1] == '1') {
		str[length-1] = '4';
		up(str, length-1);
	} else if (str[length-1] == '2') {
		str[length-1] = '3';
		up(str, length-1);
	}
}

void down(char str[], int length) {
	if (length == 0) {good = 0;}
	if (str[length-1] == '1') {
		str[length-1] = '4';
	} else if (str[length-1] == '2') {
		str[length-1] = '3';
	} else if (str[length-1] == '4') {
		str[length-1] = '1';
		down(str, length-1);
	} else if (str[length-1] == '3') {
		str[length-1] = '2';
		down(str, length-1);
	}
}

void left(char str[], int length) {
	if (length == 0) {good = 0;}
	if (str[length-1] == '2') {
		str[length-1] = '1';
	} else if (str[length-1] == '3') {
		str[length-1] = '4';
	} else if (str[length-1] == '1') {
		str[length-1] = '2';
		left(str, length-1);
	} else if (str[length-1] == '4') {
		str[length-1] = '3';
		left(str, length-1);
	}
}

void right(char str[], int length) {
	if (length == 0) {good = 0;}
	if (str[length-1] == '1') {
		str[length-1] = '2';
	} else if (str[length-1] == '4') {
		str[length-1] = '3';
	} else if (str[length-1] == '2') {
		str[length-1] = '1';
		right(str, length-1);
	} else if (str[length-1] == '3') {
		str[length-1] = '4';
		right(str, length-1);
	}
}

int main() {

char pos[256], moves[256];
int length, i;

cin >> pos;
length = strlen(pos);

do {

cin >> moves;

good = 1;
for (i=0; moves[i]!='\0'; i++) {
	if (moves[i] == 'R') {
		right(pos, length);
	} else if (moves[i] == 'L') {
		left(pos, length);
	} else if (moves[i] == 'U') {
		up(pos, length);
	} else if (moves[i] == 'D') {
		down(pos, length);
	}
	if (good == 0) {break;}
}

if (good == 0) {cout << "OUT" << endl;}
else {cout << pos << endl;}

cin >> pos;
length = strlen(pos);

} while (strcmp(pos, "END")!=0);

return 0;
}
