#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

long long m[128][128];
bool v[128][128];

void flood(int i, int j) {
    v[i][j] = true;
    if (!v[i+1][j] && m[i][j] == m[i+1][j]) flood(i+1,j);
    if (!v[i-1][j] && m[i][j] == m[i-1][j]) flood(i-1,j);
    if (!v[i][j+1] && m[i][j] == m[i][j+1]) flood(i,j+1);
    if (!v[i][j-1] && m[i][j] == m[i][j-1]) flood(i,j-1);
}

int main() {
    int N, x[2][64], y[2][64], xx[128], yy[128], i, j, k, NN, MX, MY, RES;
    double tmpx, tmpy;
    long long mask;

    while (cin >> N && N) {
        for (i=0; i<N; i++) {
            cin >> x[0][i] >> y[0][i] >> x[1][i] >> y[1][i];
            xx[i] = x[0][i]; xx[N+i] = x[1][i];
            yy[i] = y[0][i]; yy[N+i] = y[1][i];
        }
        xx[2*N] = yy[2*N] = -1; xx[2*N+1] = yy[2*N+1] = 1000001; NN = 2*N+2;
        sort(xx, xx+NN); sort(yy, yy+NN);

        for (i=MX=1; i<NN; i++) if (xx[i] != xx[i-1]) {
            for (j=MY=1; j<NN; j++) if (yy[j] != yy[j-1]) {
                mask = 0LL; tmpx = (xx[i]+xx[i-1])/2.0; tmpy = (yy[j]+yy[j-1])/2.0;
                for (k=0; k<N; k++) if (tmpx > x[0][k] && tmpx < x[1][k] && tmpy > y[1][k] && tmpy < y[0][k]) mask ^= (1LL<<k);
                m[MX][MY] = mask;
                MY++;
            }
            MX++;
        }

        memset(v, false, sizeof(v));
        for (i=0; i<=MX; i++) v[i][0] = v[i][MY] = true;
        for (i=0; i<=MY; i++) v[0][i] = v[MX][i] = true;

//        for (i=1; i<MY; i++) {
//            for (j=1; j<MX; j++) cout << m[j][i] << ' '; cout << endl;
//        }
//        cout << endl;

        RES = 0;
        for (i=1; i<MX; i++) for (j=1; j<MY; j++) if (!v[i][j]) {RES++; flood(i, j);}
        cout << RES << endl;
    }

    return 0;
}
