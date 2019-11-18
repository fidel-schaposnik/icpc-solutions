#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int N, c, p, g;

    while (cin >> N && N) {
        c = p = (2*N)/7;

        g = (2*N)%7;
        if (g >= 5) { c++; g -= 5; }
        else if (g >= 2) { p++; g -= 2; }

        printf("%.1lf %.1lf %.1lf %.1lf\n", g/2., p/2., p/2., c/2.);
    }

    return 0;
}
