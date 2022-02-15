#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int T, t, i, c[10];
    char tmp[7];
    bool flag;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> tmp; flag = true;

        memset(c, 0, sizeof(c));
        for (i=0; i<6; i++) c[tmp[i]-'0']++;
        for (i=0; i<=9; i++) if (c[i] >= 3) flag = false;
        
        for (i=0; i<=3 && flag; i++) {
            if ( (tmp[i] == tmp[i+1]+1 && tmp[i+1] == tmp[i+2]+1) || (tmp[i] == tmp[i+1]-1 && tmp[i+1] == tmp[i+2]-1) ) flag = false;
        }
        if (flag) cout << "ACCEPTABLE" << endl;
        else cout << "WEAK" << endl;
    }

    return 0;
}
