#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 1000

#define ISRING(c) ( (c)>='a' && (c)<='z' )
#define KEYTYPE(c) ( (c)<='M' ? 0 : 1 )

int R, r[32], k[32][2], E, f[32], TOTAL_KEYS[2], BEST_KEYS, BEST_RINGS;
bool rings[32];

struct node {
    int p, k[2];
    vector<int> c;
} n[32];

struct edge {
    int a, b;
} e[32];

int ring_id(char c) {
    if (!rings[c-'a']) {
        n[c-'a'].c.clear();
        r[R++] = c-'a';
        rings[c-'a'] = true;
    }
    return c-'a';
}

int getf(int cur) {
    if (f[cur] != cur) f[cur] = getf(f[cur]);
    return f[cur];
}

int out[2], cant[32][2];

void fill(int cur) {
    n[cur].k[0] = cant[cur][0];
    n[cur].k[1] = cant[cur][1];
    for (int i=0; i<(int)n[cur].c.size(); i++) {
        int next = n[cur].c[i];
        if (next == n[cur].p) continue;
        fill(next);
        n[cur].k[0] += n[next].k[0];
        n[cur].k[1] += n[next].k[1];
    }
}

int dp[32][2];

int _dp(int cur, int type) {
    if (dp[cur][type] == -1) {
        if (cant[cur][1-type] > 0 || n[cur].k[type] == 0) dp[cur][type] = INF;
        else if (n[cur].k[1-type] == 0) dp[cur][type] = 0;
        else {
            dp[cur][type] = 0; int tmp = 0;
            for (int i=0; i<(int)n[cur].c.size(); i++) {
                int next = n[cur].c[i];
                if (next == n[cur].p) continue;
    
                if (n[next].k[1-type] > 0 && n[next].k[type] == 0) {dp[cur][type]++; tmp++;}
                else if (n[next].k[1-type] > 0 && n[next].k[type] > 0) {
                    dp[cur][type] += min(2 + _dp(next, 1-type), _dp(next, type));
                    tmp++;
                }
            }
            dp[cur][type] += tmp-1;
        }
    }
    return dp[cur][type];
}

void dfs(int cur, bool move) {
    if (cur == R) {
        if (out[0] == TOTAL_KEYS[0]) {
            for (int i=0; i<R; i++) if (k[r[i]][0] != k[r[i]][1] || k[r[i]][0]+k[r[i]][1] == 0) {
                if (cant[r[i]][1] != 0 && !move) continue;

                cant[r[i]][1] = 0; out[1] += k[r[i]][1];
                cant[r[i]][0] = out[0]; out[0] = 0;
                dfs(cur, false);
                cant[r[i]][0] = 0; out[0] = TOTAL_KEYS[0];
                cant[r[i]][1] = k[r[i]][1]; out[1] -= k[r[i]][1];
            }
        } else if (out[1] == TOTAL_KEYS[1]) {
            for (int i=0; i<R; i++) if (k[r[i]][0] != k[r[i]][1] || k[r[i]][0]+k[r[i]][1] == 0) {
                if (cant[r[i]][0] != 0 && !move) continue;

                cant[r[i]][0] = 0; out[0] += k[r[i]][0];
                cant[r[i]][1] = out[1]; out[1] = 0;
                dfs(cur, false);
                cant[r[i]][1] = 0; out[1] = TOTAL_KEYS[1];
                cant[r[i]][0] = k[r[i]][0]; out[0] -= k[r[i]][0];
            }
        } else {
            int i, j, c[2], KEYS = out[0] + out[1], RINGS;
            for (i=0; i<R; i++) for (j=0; j<2; j++) KEYS += abs(cant[r[i]][j]-k[r[i]][j]);
            if (KEYS > BEST_KEYS) return;

            for (i=0; i<R; i++) if (getf(r[i]) == r[i]) fill(r[i]);
            memset(dp, -1, sizeof(dp));

            c[0] = c[1] = RINGS = 0;
            for (i=0; i<R; i++) if (getf(r[i]) == r[i]) {
                if (n[r[i]].k[0] == 0 && n[r[i]].k[1] > 0) c[1]++;
                else if (n[r[i]].k[0] > 0 && n[r[i]].k[1] == 0) c[0]++;
                else if (n[r[i]].k[0] > 0 && n[r[i]].k[1] > 0) {
                    c[0]++; c[1]++;
                    RINGS += min(_dp(r[i], 0), _dp(r[i], 1));
                }
            }
            RINGS += c[0]+c[1]-2;
            if (KEYS < BEST_KEYS || (KEYS == BEST_KEYS && RINGS < BEST_RINGS)) {BEST_KEYS = KEYS; BEST_RINGS = RINGS;}
        }
    } else {
        if (k[r[cur]][0] == 0 || k[r[cur]][1] == 0) {
            cant[r[cur]][0] = k[r[cur]][0];
            cant[r[cur]][1] = k[r[cur]][1];
            dfs(cur+1, move);
        } else if (k[r[cur]][0] > k[r[cur]][1]) {
            cant[r[cur]][0] = k[r[cur]][0];
            cant[r[cur]][1] = 0; out[1] += k[r[cur]][1];
            dfs(cur+1, move); out[1] -= k[r[cur]][1];
        } else if (k[r[cur]][1] > k[r[cur]][0]) {
            cant[r[cur]][1] = k[r[cur]][1];
            cant[r[cur]][0] = 0; out[0] += k[r[cur]][0];
            dfs(cur+1, move); out[0] -= k[r[cur]][0];
        } else {
            cant[r[cur]][0] = k[r[cur]][0];
            cant[r[cur]][1] = 0; out[1] += k[r[cur]][1];
            dfs(cur+1, move); out[1] -= k[r[cur]][1];
            cant[r[cur]][1] = k[r[cur]][1];
            cant[r[cur]][0] = 0; out[0] += k[r[cur]][0];
            dfs(cur+1, move); out[0] -= k[r[cur]][0];
        }
    }
}

int count() {
    int RES = 0;
    for (int i=0; i<R; i++) if (getf(r[i]) == r[i] && cant[r[i]][0] + cant[r[i]][1] > 0) RES++;
    return RES-1;
}

int dfs2(int cur) {
    for (int i=0; i<(int)n[cur].c.size(); i++) {
        int next = n[cur].c[i];
        if (next == n[cur].p) continue;
        n[next].p = cur;
        dfs2(next);
    }
}

int main() {
    int i, fa, fb, CASE = 1;
    char tmp[4];

    while (cin >> tmp) {
        memset(k, 0, sizeof(k)); TOTAL_KEYS[0] = TOTAL_KEYS[1] = 0;
        memset(rings, false, sizeof(rings)); E = R = 0;
        do {
            if (ISRING(tmp[0]) && ISRING(tmp[1])) {
                e[E].a = ring_id(tmp[0]);
                e[E].b = ring_id(tmp[1]);
                n[e[E].a].c.push_back(e[E].b);
                n[e[E].b].c.push_back(e[E].a);
                E++;
            } else {
                if (ISRING(tmp[1])) swap(tmp[0], tmp[1]);
                k[ring_id(tmp[0])][KEYTYPE(tmp[1])]++;
                TOTAL_KEYS[KEYTYPE(tmp[1])]++;
            }
            cin >> tmp;
        } while (tmp[0] != '0');

        for (i=0; i<R; i++) {f[r[i]] = r[i]; cant[r[i]][0] = k[r[i]][0]; cant[r[i]][1] = k[r[i]][1];}
        for (i=0; i<E; i++) {
            fa = getf(e[i].a); fb = getf(e[i].b);
            if (fa != fb) {
                f[fa] = fb;
                cant[fb][0] += cant[fa][0];
                cant[fb][1] += cant[fa][1];
            }
        }
        for (i=0; i<R; i++) if (getf(r[i]) == r[i]) { n[r[i]].p = -1; dfs2(r[i]); }

        cout << "Case " << CASE++ << ": ";
        if (TOTAL_KEYS[0] == 0 && TOTAL_KEYS[1] == 0) cout << "0 0" << endl;
        else if (TOTAL_KEYS[0] == 0 || TOTAL_KEYS[1] == 0) cout << "0 " << count() << endl;
        else if (R == 1) cout << "impossible" << endl;
        else {
            BEST_KEYS = BEST_RINGS = INF;
            out[0] = out[1] = 0;
            dfs(0, true);
            cout << BEST_KEYS << ' ' << BEST_RINGS << endl;
        }
    }

    return 0;
}
