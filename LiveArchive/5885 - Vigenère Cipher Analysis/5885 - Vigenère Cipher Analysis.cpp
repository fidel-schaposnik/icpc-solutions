#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define MAXN 100100
#define MAXK 101
#define KEY(c1,c2) ( (char)(((c1)-(c2)+25)%26 + 'A') )
#define VALUE(c) ( (c)-'A' )

typedef unsigned long long HASH;

struct key {
    HASH h;
    int pos;
    key(HASH H=0ULL, int POS=0) {
        h = H; pos = POS;
    }
};

bool operator<(const key &k1, const key &k2) {
    if (k1.h != k2.h) return k1.h < k2.h;
    else return k1.pos < k2.pos;
}

int W[2], C;
HASH h[2][MAXN][MAXK], pow33[MAXK];
char c[MAXN], w[2][MAXK];

bool check(int cur, int pos, int k) {
    for (int i=k; i<W[cur]; i++) {
        int tmp = i%k;
        if (KEY(c[pos+i],w[cur][i]) != KEY(c[pos + i%k],w[cur][i%k])) return false;
    }
    return true;
}

HASH calc_hash(int cur, int pos, int a, int b) {
    return h[cur][pos][b] - h[cur][pos][a]*pow33[b-a];
}

HASH getkey(int cur, int pos, int k) {
    int tmp = pos%k;
    return calc_hash(cur, pos, k - tmp, k)*pow33[k-tmp] + calc_hash(cur, pos, 0, k - tmp);
}

void generate_keys(int cur, int k, vector<key> &v) {
    v.clear();
    for (int i=0; i<=C-W[cur]; i++) {
        h[cur][i][k] = h[cur][i][k-1]*33ULL + VALUE(KEY(c[i+k-1], w[cur][k-1]));
        if (check(cur, i, k) == true) v.push_back(key(getkey(cur, i, k), i));
    }
}

string decrypt(string k) {
    string RES = "";
    for (int i=0; i<C; i++) RES += KEY(c[i], k[i%k.size()]);
    return RES + "\n";
}

bool nointersect(int a, int b, int c, int d) {
    return (b <= c || a >= d);
}

string findkey(int pos, int k) {
    string RES = "";
    for (int i=0; i<k; i++) RES += KEY(c[pos+i],w[0][i]);
    RES = RES.substr(k - pos%k, k) + RES.substr(0, k - pos%k);
    return RES;
}

HASH repeat(HASH h, int times, int len) {
    HASH RES = 0ULL;
    while (times > 0) {
        if ((times&1) == 1) RES = RES*pow33[len] + h;
        h = h*pow33[len] + h;
        len *= 2;
        times >>= 1;
    }
    return RES;
}

int gcd(int a, int b) {
    if (a == 0 || b == 0) return a+b;
    else return gcd(b, a%b);
}

int find(vector<key> &v, int cur) {
    int s=0, e = (int)v.size() - cur + 1;
    while (e-s > 1) {
        int m = (s+e)/2;
        if (v[cur].h == v[cur+m].h) s = m;
        else e = m;
    }
    return s+1;
}

int main() {
    int K, i, j, k, di, dj, V1, V2, keysize, keypos;
    vector<key> v1, v2;
    HASH keyhash;
    bool FLAG;

    pow33[0] = 1ULL;
    for (i=1; i<MAXK; i++) pow33[i] = pow33[i-1]*33ULL;

    while (scanf("%d", &K) && K!=0) {
        for (i=0; i<2; i++) {
            scanf("%s", w[i]); W[i] = strlen(w[i]);
        }
        scanf("%s", c); C = strlen(c);
    
        for (i=0; i<2; i++) for (j=0; j<C; j++) h[i][j][0] = 0ULL;
        keysize = keypos = -1; keyhash = 0ULL; FLAG = false;
        for (k=1; k<=K && !FLAG; k++) {
            generate_keys(0, k, v1); V1 = (int)v1.size();
            generate_keys(1, k, v2); V2 = (int)v2.size();
            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());

            i = j = 0;
            while (i < V1 && j < V2 && !FLAG) {
                if (v1[i].h == v2[j].h) {
                    di = find(v1, i);
                    dj = find(v2, j);
                    if (nointersect(v1[i].pos, v1[i].pos+W[0], v2[j+dj-1].pos, v2[j+dj-1].pos+W[1]) == true) {
                        if (keysize == -1) {
                            keysize = k; keypos = v1[i].pos; keyhash = v1[i].h;
                        } else {
                            int tmp = gcd(keysize, k);
                            if (repeat(keyhash, k/tmp, keysize) != repeat(v1[i].h, keysize/tmp, k)) FLAG = true;
                        }
                    }
                    i+=di; j+=dj;
                } else if (v1[i].h < v2[j].h) i += find(v1, i);
                else j += find(v2, j);
            }
        }
        if (FLAG) printf("ambiguous\n");
        else if (keysize == -1) printf("impossible\n");
        else printf(decrypt(findkey(keypos, keysize)).c_str());
    }

    return 0;
}
