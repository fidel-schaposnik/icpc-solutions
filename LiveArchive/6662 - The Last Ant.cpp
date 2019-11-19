#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int N, d[32], x[32], X, i, OUT, t, cur[128], last_t, last;
    char tmp;

    while (cin >> N >> X && (N || X)) {
        for (i=1; i<=N; i++) {
            cin >> tmp >> x[i];
            d[i] = ( tmp=='L' ? -1 : 1);
        }
    
        OUT = t = last_t = last = 0;
        while (OUT < N) {
            memset(cur, 0, sizeof(cur));
            for (i=1; i<=N; i++) if (x[i] > 0 && x[i] < X) {
                x[i] += d[i];
                if (cur[x[i]]) { d[cur[x[i]]] *= -1; d[i] *= -1; }
                cur[x[i]] = i;
                if (x[i] == 0 || x[i] == X) {
                    OUT++;
                    if ( last_t < t+1 || (last_t == t+1 && d[i] == -1) ) { last_t = t+1; last = i; }
                }
            }
            t++;
        }
        cout << t << ' ' << last << endl;
    }

    return 0;
}
