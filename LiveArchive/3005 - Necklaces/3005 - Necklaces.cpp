#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

void strrev(char str[], int length) {
	char toret[length+1];
	int i;
	for (i=0; i<length; i++) {
		toret[i] = str[length-1-i];
	}
	toret[length] = '\0';
	strcpy(str, toret);
}

int char_to_int(char neck[], int len, char one, int start) {
	int i, num;
	num = 0;
	for (i=start; i<start+len; i++) {
		if (neck[i%len] == one) {
			num = num*2 + 1;
		} else {
			num = num*2;
		}
	}
	return num;
}

int main() {

int length, min, max, i, j, cur;
char neck[31], letters[] = "BW";

scanf("%s", neck);
length = strlen(neck);

do {

min = max = char_to_int(neck, length, 'B', 0);
for (i=0; i<length; i++) {
	for (j=0; j<2; j++) {
		cur = char_to_int(neck, length, letters[j], i);
		if (cur < min) {min = cur;}
		if (cur > max) {max = cur;}
	}
}

strrev(neck, length);

for (i=0; i<length; i++) {
	for (j=0; j<2; j++) {
		cur = char_to_int(neck, length, letters[j], i);
		if (cur < min) {min = cur;}
		if (cur > max) {max = cur;}
	}
}

cout << min << " " << max << endl;

scanf("%s", neck);
length = strlen(neck);

} while (strcmp(neck, "END")!=0);

return 0;
}
