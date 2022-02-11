#include <iostream>
#include <string>
using namespace std;

int main() {
	int i, tmp;
	string s;
	
	while (cin >> s && s != "#") {
		tmp = 0;
		for (i=0; i<(int)s.size()-1; i++) tmp += s[i]-'0';
		if ( (s[s.size()-1] == 'e' && tmp%2 == 0) || (s[s.size()-1] == 'o' && tmp%2 == 1) ) cout << s.substr(0,s.size()-1)+"0" << endl;
		else cout << s.substr(0,s.size()-1)+"1" << endl;
	}

	return 0;
}
