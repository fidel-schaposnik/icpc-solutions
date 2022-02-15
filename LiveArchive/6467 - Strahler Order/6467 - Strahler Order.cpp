#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1024

struct node {
    vector<int> out;
    int in, o, rep;
} n[MAXN];

int s[MAXN];

int main() {
    int T, t, ID, N, EDGES, i, a, b, S, E, cur, next;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> N >> EDGES;
        for (i=1; i<=N; i++) {
            n[i].out.clear();
            n[i].in = 0;
            n[i].o = n[i].rep = 0;
        }

        for (i=0; i<EDGES; i++) {
            cin >> a >> b;
            n[a].out.push_back(b);
            n[b].in++;
        }

        S = E = 0;
        for (i=1; i<=N; i++) if (!n[i].in) { s[E++] = i; n[i].o = 1; }
        while (S < E) {
            cur = s[S++];
            if (n[cur].rep >= 2) n[cur].o++;
            for (i=0; i<(int)n[cur].out.size(); i++) {
                next = n[cur].out[i];
                n[next].in--;
                if (!n[next].in) s[E++] = next;

                if (n[cur].o > n[next].o) { n[next].o = n[cur].o; n[next].rep = 1; }
                else if (n[cur].o == n[next].o) n[next].rep++;
            }
        }
        cout << ID << ' ' << n[N].o << endl;
    }

    return 0;
}
