#include <iostream>
#include <string>
using namespace std;

#define MAXN 16

int main() {
	int i, a, b, r, stack[MAXN], STACK;
	string s;
	
	while (cin >> s >> r) {
		a = s[0]-'0';
		for (i=1; i<(int)s.size(); i+=2) {
			if (s[i] == '+') a += s[i+1]-'0';
			else a *= s[i+1]-'0';
		}
		
		b = s[0]-'0'; STACK = 0;
		for (i=1; i<(int)s.size(); i+=2) {
			if (s[i] == '+') {
				stack[STACK++] = b;
				b = s[i+1]-'0';
			} else b *= s[i+1]-'0';
		}
		for (i=0; i<STACK; i++) b += stack[i];
		
		if (a == r && b == r) cout << 'U' << endl;
		else if (b == r) cout << 'M' << endl;
		else if (a == r) cout << 'L' << endl;
		else cout << 'I' << endl;
	}
	
	return 0;
}
