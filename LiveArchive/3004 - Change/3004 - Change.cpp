#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct money {
	char name[5];
	int val;
	int quant;
};

int main() {

int pur_d, rec_d, pur_c, rec_c;
int pur, rec, i, toret;
bool first;

money change[9];
strcpy(change[0].name, "$20");
change[0].val = 2000;
strcpy(change[1].name, "$10");
change[1].val = 1000;
strcpy(change[2].name, "$5");
change[2].val = 500;
strcpy(change[3].name, "$2");
change[3].val = 200;
strcpy(change[4].name, "$1");
change[4].val = 100;
strcpy(change[5].name, "50c");
change[5].val = 50;
strcpy(change[6].name, "20c");
change[6].val = 20;
strcpy(change[7].name, "10c");
change[7].val = 10;
strcpy(change[8].name, "5c");
change[8].val = 5;

scanf("%d.%d %d.%d", &pur_d, &pur_c, &rec_d, &rec_c);

pur = pur_d*100 + pur_c;
rec = rec_d*100 + rec_c;

do {

for (i=0; i<9; i++) {
	change[i].quant = 0;
}

if (pur%10 == 1 || pur%10 == 2) {
	pur = (pur/10)*10;
} else if (pur%10 == 3 || pur%10 == 4 || pur%10 == 6 || pur%10 == 7) {
	pur = (pur/10)*10 + 5;
} else if (pur%10 == 8 || pur%10 == 9) {
	pur = ((pur/10)+1)*10;
}

if (rec < pur) {
	cout << "Not enough money offered." << endl;
} else if (rec == pur) {
	cout << "Exact amount." << endl;
} else {
	toret = rec - pur;
	for (i=0; i<9; i++) {
		change[i].quant = toret/change[i].val;
		toret = toret%change[i].val;
	}

	first = 1;
	for (i=0; i<9; i++) {
		if (change[i].quant != 0) {
			if (first == 0) {
				cout << " ";
			}
			cout << change[i].name << "*" << change[i].quant;
			first = 0;
		}
	}
	cout << endl;
}

scanf("%d.%d %d.%d", &pur_d, &pur_c, &rec_d, &rec_c);

pur = pur_d*100 + pur_c;
rec = rec_d*100 + rec_c;

} while (pur != 0 || rec != 0);

return 0;
}
