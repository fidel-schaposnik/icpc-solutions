#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define MAXN 1048576

struct mirror {
    int t, p;
    mirror(int type=0, int pos=0) {
        t=type; p=pos;
    }
};

bool operator<(const mirror &m1, const mirror &m2) {
    return m1.p < m2.p;
}

struct pt {
    int r, c;
    pt(int row=0, int col=0) {
        r=row; c=col;
    }
};

bool operator<(const pt &p1, const pt &p2) {
    if (p1.r != p2.r) return p1.r < p2.r;
    else return p1.c < p2.c;
}

set<mirror> r[MAXN], c[MAXN];

int dr[4] = {0, -1, 1,  0};
int dc[4] = {1,  0, 0, -1};
int act[2][4] = {{1, 0, 3, 2}, {2, 3, 0, 1}};
int R, C;

void trace(pt cur, int d, vector<pt> &RES) {
    set<mirror>::iterator tmp;
    RES.clear(); RES.push_back(cur);
    do {
        if (d == 0) {
            tmp = r[cur.r].upper_bound(mirror(0, cur.c));
            if (tmp != r[cur.r].end()) RES.push_back(pt(cur.r, tmp->p));
            else {
                RES.push_back(pt(cur.r, C+1));
                break;
            }
        } else if (d == 2) {
            tmp = c[cur.c].upper_bound(mirror(0, cur.r));
            if (tmp != c[cur.c].end())RES.push_back(pt(tmp->p, cur.c));
            else {
                RES.push_back(pt(R+1, cur.c));
                break;
            }
        } else if (d == 1) {
            tmp = c[cur.c].lower_bound(mirror(0, cur.r));
            if (tmp != c[cur.c].begin()) {tmp--; RES.push_back(pt(tmp->p, cur.c));}
            else {
                RES.push_back(pt(0, cur.c));
                break;
            }
        } else if (d == 3) {
            tmp = r[cur.r].lower_bound(mirror(0, cur.c));
            if (tmp != r[cur.r].begin()) {tmp--; RES.push_back(pt(cur.r, tmp->p));}
            else {
                RES.push_back(pt(cur.r, 0));
                break;
            }
        }
        d = act[tmp->t][d];
        cur = RES.back();
    } while (true);
}

vector<pt> t[2];

struct seg {
    int p, s, e;
    seg(int pos=0, int start=0, int end=0) {
        p=pos; s=start; e=end;
    }
};

bool operator<(const seg &s1, const seg &s2) {
    if (s1.p != s2.p) return s1.p < s2.p;
    else if (s1.s != s2.s) return s1.s < s2.s;
    else return s1.e < s2.e;
}

vector<seg> s[2][2];

void split_seg(vector<pt> &p, vector<seg> &h, vector<seg> &v) {
    h.clear(); v.clear();
    for (int i=1; i<(int)p.size(); i++) {
        if (p[i-1].r == p[i].r) h.push_back(seg(p[i].r, min(p[i-1].c, p[i].c), max(p[i-1].c, p[i].c)));
        else v.push_back(seg(p[i].c, min(p[i-1].r, p[i].r), max(p[i-1].r, p[i].r)));
    }
}

struct event {
    int t, p, v;
    event(int val=0, int pos=0, int time=0) {
        t=time; p=pos; v=val;
    }
};

bool operator<(const event &e1, const event &e2) {
    if (e1.t != e2.t) return e1.t < e2.t;
    else if (e1.v != e2.v) return e1.v < e2.v;
    else return e1.p < e2.p;
}

int get_cf(int idx, int *bit) {
	int cf = bit[0];
	while (idx > 0) {
        cf += bit[idx];
		idx &= idx-1;
	}
	return cf;
}

void upd_f(int idx, int f, int *bit) {
	if (idx == 0) bit[idx] += f;
    else while (idx < MAXN) {
        bit[idx] += f;
        idx += idx&(-idx);
	}
}

int get_f(int idx, int *bit) {
    int f = bit[idx];
	if (idx > 0) {
        int p = idx&(idx-1); idx--;
		while (p != idx) {
            f -= bit[idx];
			idx &= idx-1;
		}
	}
   return f;
}


vector<event> e;
int bit[MAXN];

long long inter(vector<seg> &v, vector<seg> &h, pt &first) {
    int i, j;
    long long RES;

    e.clear();
    for (i=0; i<(int)h.size(); i++) {
        e.push_back(event(1, h[i].p, h[i].s));
        e.push_back(event(-1, h[i].p, h[i].e));
    }
    sort(e.begin(), e.end());
    sort(v.begin(), v.end());

    i = j = 0; first = pt(MAXN, MAXN); RES = 0LL;
    while (i < e.size() || j < v.size()) {
        if (i == (int)e.size()) { RES += get_cf(v[j].e-1, bit) - get_cf(v[j].s, bit); j++; }
        else if (j == (int)v.size()) { upd_f(e[i].p, e[i].v, bit); i++; }
        else if (e[i].t < v[j].p) { upd_f(e[i].p, e[i].v, bit); i++; }
        else if (v[j].p < e[i].t) { RES += get_cf(v[j].e-1, bit) - get_cf(v[j].s, bit); j++; }
        else if (e[i].v == -1) { upd_f(e[i].p, e[i].v, bit); i++; }
        else { RES += get_cf(v[j].e-1, bit) - get_cf(v[j].s, bit); j++; }

        if (RES > 0LL && first.r == MAXN && first.c == MAXN) for (int k=v[j-1].s+1; k<v[j-1].e; k++) if (get_f(k, bit) > 0) {first.r = v[j-1].p; first.c = k; break;}
    }
    return RES;
}

int main() {
    int N[2], i, j, tmpr, tmpc, CASE = 1;
    pt first[2], RESPT;
    long long RES;

    while (cin >> R >> C >> N[0] >> N[1]) {
        for (i=1; i<=R; i++) r[i].clear();
        for (i=1; i<=C; i++) c[i].clear();

        for (i=0; i<2; i++) for (j=0; j<N[i]; j++) {
            cin >> tmpr >> tmpc;
            r[tmpr].insert(mirror(i, tmpc));
            c[tmpc].insert(mirror(i, tmpr));
        }

        trace(pt(1,0), 0, t[0]);

        cout << "Case " << CASE++ << ": ";
        if (t[0].back().r == R && t[0].back().c == C+1) cout << 0 << endl;
        else {
            trace(pt(R,C+1), 3, t[1]);
    
            for (i=0; i<2; i++) split_seg(t[i], s[i][0], s[i][1]);
    
            RES = inter(s[0][0], s[1][1], first[0]);
            RES += inter(s[1][0], s[0][1], first[1]);
            RESPT = min(first[0], first[1]);
            if (RES == 0) cout << "impossible" << endl;
            else cout << RES << ' ' << RESPT.r << ' ' << RESPT.c << endl;
        }
    }

    return 0;
}
