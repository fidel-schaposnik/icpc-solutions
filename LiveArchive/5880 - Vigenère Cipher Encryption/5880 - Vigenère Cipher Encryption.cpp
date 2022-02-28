#include <iostream>
#include <string>
using namespace std;

char encrypt(char c, char k) {
    return (char)( (c-'A' + k-'A'+1)%26 + 'A' );
}

int main() {
    string m, k;

    while (cin >> k && k!="0") {
        cin >> m;
        for (int i=0; i<(int)m.size(); i++) cout << encrypt(m[i], k[i%k.size()]); cout << endl;
    }

    return 0;
}
