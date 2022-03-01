#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

int main() {

map<char, string> enc;
map<char, string>::iterator eiter;

map<string, char> dec;

string encrypted;
char input[128], tmp[8];
int i, L, l[128], pos, k, K;

enc.clear();
enc['A'] = ".-";
enc['H'] = "....";
enc['O'] = "---";
enc['V'] = "...-";
enc['B'] = "-...";
enc['I'] = "..";
enc['P'] = ".--.";
enc['W'] = ".--";
enc['C'] = "-.-.";
enc['J'] = ".---";
enc['Q'] = "--.-";
enc['X'] = "-..-";
enc['D'] = "-..";
enc['K'] = "-.-";
enc['R'] = ".-.";
enc['Y'] = "-.--";
enc['E'] = ".";
enc['L'] = ".-..";
enc['S'] = "...";
enc['Z'] = "--..";
enc['F'] = "..-.";
enc['M'] = "--";
enc['T'] = "-";
enc['G'] = "--.";
enc['N'] = "-.";
enc['U'] = "..-";
enc['_'] = "..--";
enc['.'] = "---.";
enc[','] = ".-.-";
enc['?'] = "----";

dec.clear();
for (eiter=enc.begin(); eiter!=enc.end(); eiter++) {
   dec[(*eiter).second] = (*eiter).first;
}

cin >> K;

for (k=1; k<=K; k++) {

cin >> input;
L = strlen(input);

encrypted = "";
for (i=0; i<L; i++) {
   encrypted.append(enc[input[i]]);
	l[i] = enc[input[i]].size();
}

cout << k << ": ";

pos = 0;
for (i=L-1; i>=0; i--) {
   cout << dec[encrypted.substr(pos, l[i])];
	pos += l[i];
}
cout << endl;

}

return 0;
}
