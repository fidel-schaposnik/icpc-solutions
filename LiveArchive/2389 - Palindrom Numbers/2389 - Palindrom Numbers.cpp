#include <iostream>
using namespace std;

bool is_pal(int num, int base) {
	int rep[16], count, i;
	bool result;

	count=0;
	while (num!=0) {
		rep[count] = num%base;
		num = num/base;
		count++;
	}

	for (i=0; i<count/2; i++) {
		if (rep[i] != rep[count-1-i]) {return 0;}
	}
	return 1;
}

int main() {

int n, count, i, pals[16];

cin >> n;

do {

count=0;
for (i=2; i<=16; i++) {
	if (is_pal(n, i)==1) {
		pals[count] = i;
		count++;
	}
}

if (count==0) {
	cout << "Number " << n << " is not palindrom" << endl;
} else {
	cout << "Number " << n << " is palindrom in basis";
	for (i=0; i<count; i++) {
		cout << " " << pals[i];
	}
	cout << endl;
}

cin >> n;

} while (n!=0);

return 0;
}
