#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct word {
	char w[32];
	int freq;
};

int main() {

bool started;
int pos, count, i, best;
char temp[32], c;
word words[2000];

while (1) {

best = -1;
count = started = 0;
while (1) {
	c = getchar();
	if (c == '#') {break;}

	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) {
		if (c >= 65 && c <= 90) {c += 32;}
		if (started == 0) {
			started = 1;
			temp[0] = c;
			pos = 1;
		} else {
			temp[pos] = c;
			pos++;
		}
	}

	else {
		if (started == 1) {
			temp[pos] = '\0';
			for (i=0; i<count; i++) {
				if (strcmp(words[i].w, temp) == 0) {
					words[i].freq++;
					if (best == -1 || words[i].freq > words[best].freq) {best = i;}
					started = 0;
					break;
				}
			}
			if (started == 1) {
				strcpy(words[count].w, temp);
				words[count].freq = 1;
				if (best == -1) {best = count;}
				count++;
				started = 0;
			}
		}
	}
}

if (best != -1) {
	if (words[best].freq < 10) {cout << " ";}
	if (words[best].freq < 100) {cout << " ";}
	if (words[best].freq < 1000) {cout << " ";}
	cout << words[best].freq << " " << words[best].w << endl;
} else {
	break;
}

}

return 0;
}
