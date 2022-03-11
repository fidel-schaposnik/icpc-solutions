#include <iostream>
#include <cstdio>
using namespace std;

int v[26], V, S;
bool stack[256];

int valid(char *x, int p);
int eval(char *x, int p, int values);

int Single(char *x, int p) {
	return valid(x, p);
}

int Double(char *x, int p) {
   int first = valid(x, p);
	if (first == -1) return -1;
	else return valid(x, first);
}

int valid(char *x, int p) {
   if (x[p] >= 'a' && x[p] <= 'z') {
		if (v[x[p]-'a'] == -1) {
		   v[x[p]-'a'] = V;
			V++;
		}
	   return p+1;
	} else if (x[p] == 'C' || x[p] == 'K' || x[p] == 'A' || x[p] == 'D' || x[p] == 'E' || x[p] == 'J') return Double(x, p+1);
	else if (x[p] == 'N') return Single(x, p+1);
	else if (x[p] == '\0') return -2;
	else return -1;
}

int N(char *x, int p, int values) {
   int newp = eval(x, p, values);
	stack[S-1] = !stack[S-1];
	return newp;
}

int eDouble(char *x, int p, int values, char O) {
   int midp = eval(x, p, values);
	int newp = eval(x, midp, values);

	if (O == 'C') {
	   if (stack[S-2] == 1 && stack[S-1] == 0) stack[S-2] = 0;
		else stack[S-2] = 1;
	} else if (O == 'K') stack[S-2] = (stack[S-2]&stack[S-1]);
	else if (O == 'A') stack[S-2] = (stack[S-2]|stack[S-1]);
	else if (O == 'D') stack[S-2] = (!(stack[S-2]&stack[S-1]));
	else if (O == 'E') stack[S-2] = (stack[S-2]==stack[S-1]);
	else if (O == 'J') stack[S-2] = (stack[S-2]^stack[S-1]);
	S--;

	return newp;
}

int eval(char *x, int p, int values) {
   if (x[p] >= 'a' && x[p] <= 'z') {
		stack[S] = ((values>>v[x[p]-'a'])&1);
		S++;
	   return p+1;
	} else if (x[p] == 'N') return N(x, p+1, values);
	else if (x[p] == 'C' || x[p] == 'K' || x[p] == 'A' || x[p] == 'D' || x[p] == 'E' || x[p] == 'J') return eDouble(x, p+1, values, x[p]);
}

int main() {

char input[256];
int result, i;
bool RES[2];

while (scanf("%s", &input) != EOF) {

for (i=0; i<26; i++) {
   v[i] = -1;
}
V = 0;

result = valid(input, 0);

if (result == -2) {
   cout << input << " is invalid: insufficient operands" << endl;
} else if (result == -1) {
   cout << input << " is invalid: invalid character" << endl;
} else if (input[result] != '\0') {
   cout << input << " is invalid: extraneous text" << endl;
} else {
   cout << input << " is valid: ";
	RES[0] = RES[1] = false;
	for (i=0; i<(1<<V); i++) {
		S = 0;
	   eval(input, 0, i);
		RES[stack[0]] = true;
	}

	if (RES[0] == true && RES[1] == true) cout << "contingent" << endl;
	else if (RES[0] == true && RES[1] == false) cout << "contradiction" << endl;
	else if (RES[0] == false && RES[1] == true) cout << "tautology" << endl;
}

}

return 0;
}
