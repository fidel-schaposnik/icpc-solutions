#include <iostream>
using namespace std;

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,1,-1};
char m[16][16];

void flood(int r, int c, char cur, char next) {
    if (m[r][c] == cur) {
        m[r][c] = next;
        for (int i=0; i<4; i++) flood(r+dr[i], c+dc[i], cur, next);
    }
}

void compact() {
    int i, j, k;

    for (k=1; k<=10; k++) {
        for (i=1,j=1; j<=12; j++) if (m[j][k] != '-') m[i++][k] = m[j][k];
        for (; i<=12; i++) m[i][k] = '-';
    }
    for (i=1; i<10; i++) if (m[1][i] == '-') {
        for (j=i+1; j<=10; j++) if (m[1][j] != '-') break;
        if (j < 11) for (k=1; k<=12; k++) swap(m[k][i], m[k][j]);
    }
}

int cant(char cur) {
    int RES = 0;
    for (int i=1; i<=12; i++) for (int j=1; j<=10; j++) if (m[i][j] == cur) RES++;
    return RES;
}

void print() {
    for (int i=12; i>=1; i--) {for (int j=1; j<=10; j++) cout << m[i][j]; cout << endl;}
    cout << endl;
}

int main() {
    int N, k, i, j;
    char tmp;

    while (cin >> N && N) {
        for (i=12; i>=1; i--) for (j=1; j<=10; j++) cin >> m[i][j];
        for (i=0; i<=13; i++) m[i][0] = m[i][11] = '-';
        for (i=0; i<=11; i++) m[0][i] = m[13][i] = '-';
    
        for (i=0; i<N; i++) {
            cin >> tmp >> k; j = tmp-'a'+1;
            if (m[k][j] != '-') {
                tmp = m[k][j];
                flood(k, j, m[k][j], '*');
                if (cant('*') > 2) flood(k, j, '*', '-');
                else flood(k, j, '*', tmp);
            }
            compact();
//            print();
        }
        cout << 120-cant('-') << endl;
    }

    return 0;
}
