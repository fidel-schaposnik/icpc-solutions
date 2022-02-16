#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define ABS(x) ( (x)<0.0 ? -(x) : (x) )

#define MAXN 1024

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

int gcd(int a, int b) {
    if (!b) return a;
    else return gcd(b, a%b);
}

double a[MAXN][MAXN];

int main() {
    int N, first, second, i, j, u, v;
    string tmp;
    double *aa[MAXN], RES;

    for (i=0; i<MAXN; i++) aa[i] = a[i];

    while (cin >> tmp && tmp != "$") {
        N = (int)tmp.size();
    
        first = 0;
        for (i=0; i<N; i++) first = first*2 + (tmp[i] == 'H' ? 1 : 0);
    
        cin >> tmp; second = 0;
        for (i=0; i<N; i++) second = second*2 + (tmp[i] == 'H' ? 1 : 0);

        for (i=0; i<(1<<N); i++) for (j=0; j<(1<<N); j++) a[i][j] = 0.0;
        for (i=0; i<(1<<N); i++) {
            if (i == first) {a[i][i] = 1.0; a[i][1<<N] = 1.0;}
            else if (i == second) {a[i][i] = 1.0; a[i][1<<N] = 0.0;}
            else {
                a[i][i] = 1.0;
                a[i][(i<<1)&((1<<N)-1)] -= 0.5;
                a[i][((i<<1)&((1<<N)-1))+1] -= 0.5;
                a[i][1<<N] = 0.0;
            }
        }
        gaussjordan(aa, 1<<N, (1<<N)+1);

        RES = 0.0;
        for (i=0; i<(1<<N); i++) RES += a[i][1<<N];
        RES *= pow(2.0, -N);

        u = v = 1;
        for (i=1; i<1000; i++) for (j=1; j<1000; j++) if (gcd(i,j) == 1) {
            if (ABS(RES-i/((double)j)) < ABS(RES-u/((double)v))) {u = i; v = j;}
        }
        cout << u << '/' << v << endl;
    }

    return 0;
}
