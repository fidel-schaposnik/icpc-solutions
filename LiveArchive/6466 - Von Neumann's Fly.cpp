#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int ID, t, T;
    double A, B, C, D;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> D >> A >> B >> C;
        printf("%d %.2lf\n", ID, C*D/(A+B) );
    }

    return 0;
}
