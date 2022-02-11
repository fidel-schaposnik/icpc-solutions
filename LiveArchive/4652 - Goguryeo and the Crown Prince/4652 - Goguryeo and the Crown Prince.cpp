#include <iostream>
#include <cstdio>
#include <map>
#include <string>
using namespace std;

#define MAXN 64
#define ABS(x) ( (x)<0.0 ? -(x) : (x) )

map<string, int> n;
double a[MAXN][MAXN];

void gaussjordan(double **A, int M, int N) {
    int i, j, k, maxi;

    for (i=0; i<M; i++) {
        maxi = i;
        for (k=i+1; k<M; k++) if (ABS(A[k][i]) > ABS(A[maxi][i])) maxi = k;

        for (j=0; j<N; j++) swap(A[i][j], A[maxi][j]);

        for (j=0; j<N; j++) if (j != i) A[i][j] /= A[i][i];
        A[i][i] = 1.0;

        for (k=0; k<M; k++) if (k != i) {
            for (j=i+1; j<N; j++) A[k][j] -= A[k][i]*A[i][j];
            A[k][i] = 0;
        }
    }
}

int main() {
    int i, j, N, S;
    string s1, s2, tmps;
    double *aa[MAXN];
    map<string, int>::iterator it;

    for (i=0; i<MAXN; i++) aa[i] = a[i];

    while (cin >> s1 >> s2 && s1 != s2) {
        S = s1.size(); n.clear(); N = 0;
        for (i=0; i<=S; i++) {
            n[s1.substr(0,i)] = N++;
            if (n.find(s2.substr(0,i)) == n.end()) n[s2.substr(0,i)] = N++;
        }

        for (i=0; i<N; i++) for (j=0; j<N; j++) a[i][j] = (i == j ? 1.0 : 0.0);
        for (it=n.begin(); it!=n.end(); it++) {
            a[it->second][N] = (it->first == s1 ? 1.0 : 0.0);
            if (it->first == s1 || it->first == s2) continue;

            for (i='0'; i<='1'; i++) {
                tmps = it->first + (char)i;
                while (n.find(tmps) == n.end()) tmps = tmps.substr(1, tmps.size()-1);
                a[it->second][n[tmps]] -= 0.5;
            }
        }
        gaussjordan(aa, N, N+1);
        printf("%.3lf\n", a[n[""]][N]);
    }

    return 0;
}
