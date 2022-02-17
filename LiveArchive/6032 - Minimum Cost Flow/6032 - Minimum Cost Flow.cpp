#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

#define MAXN 512
#define MAXM 65536
#define INF 1E12

typedef double tint;

#define SQ(x) ( (x)*(x) )

struct pt {
    int x, y, z;
};

tint dist(const pt &p1, const pt &p2) {
    return sqrt(SQ(p1.x-p2.x) + SQ(p1.y-p2.y) + SQ(p1.z-p2.z));
}

struct node {
    tint d;
    pt p;
} n[MAXN];

struct edge {
    int a, b, z;
} m[MAXM];

bool operator<(const edge &e1, const edge &e2) {
    if (e1.z != e2.z) return e1.z < e2.z;
    else if (e1.a != e2.a) return e1.a < e2.a;
    else return e1.b < e2.b;
}

int f[MAXN], k[MAXN], N;
tint d[MAXN][MAXN];

int getf(int cur) {
    if (f[cur] != cur) f[cur] = getf(f[cur]);
    return f[cur];
}

void join(int a, int b) {
    if (a == b) return;

    f[b] = a; k[a] += k[b];
    for (int i=0; i<N; i++) d[a][i] = d[i][a] = min(d[a][i], d[b][i]);
}

tint check(int z) {
    int i, cur;
    vector<int> c;

    for (i=0; i<N; i++) if (getf(i) == i && n[i].p.z <= z && (k[i] > 1 || i == getf(0) || i == getf(N-1))) {c.push_back(i); n[i].d = INF;}

    set< pair<tint, int> > s;
    n[getf(0)].d = k[getf(0)]*0.5; s.insert(make_pair(n[getf(0)].d, getf(0)));
    while (!s.empty()) {
        cur = s.begin()->second;
        if (cur == getf(N-1)) break;

        s.erase(make_pair(n[cur].d, cur));
        for (i=0; i<(int)c.size(); i++) {
            if (c[i] == cur || d[cur][c[i]] == INF) continue;

            if (n[cur].d + d[cur][c[i]]+k[c[i]]*0.5-1.0 < n[c[i]].d) {
                if (n[c[i]].d < INF) s.erase(make_pair(n[c[i]].d, c[i]));
                n[c[i]].d = n[cur].d + d[cur][c[i]]+k[c[i]]*0.5-1.0;
                s.insert(make_pair(n[c[i]].d, c[i]));
            }
        }
    }
    return n[getf(N-1)].d;
}

int main() {
    int M, i, j, z[MAXN], Z, CASE;
    tint RES;

    CASE = 1;
    while (cin >> N >> M) {
        for (i=0; i<N; i++) {
            cin >> n[i].p.x >> n[i].p.y >> n[i].p.z >> k[i];
            f[i] = i; z[i] = n[i].p.z;
        }

        sort(z, z+N);
        for (i=Z=1; i<N; i++) if (z[i] != z[i-1]) z[Z++] = z[i];

        for (i=0; i<M; i++) {
            cin >> m[i].a >> m[i].b;
            m[i].a--; m[i].b--;
            m[i].z = max(n[m[i].a].p.z, n[m[i].b].p.z);
        }
        sort(m, m+M);

        for (i=0; i<N; i++) {
            d[i][i] = 0.0;
            for (j=i+1; j<N; j++) {
                if (k[i] > 0 && k[j] > 0) d[i][j] = d[j][i] = dist(n[i].p, n[j].p);
                else d[i][j] = d[j][i] = INF;
            }
        }

        RES = INF;
        for (i=j=0; i<Z; i++) {
            while (j<M && m[j].z <= z[i]) { join(getf(m[j].a), getf(m[j].b)); j++; }
            if (z[i] >= max(n[0].p.z, n[N-1].p.z)) RES = min(RES, check(z[i]));
        }
        if (RES < INF) printf("Case %d: %.4lf\n", CASE++, RES);
        else printf("Case %d: impossible\n", CASE++);
    }

    return 0;
}
