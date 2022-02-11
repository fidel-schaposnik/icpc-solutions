#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define EPS 1E-9
#define DT 0.0000005

typedef double tint;

#define SQ(x) ( (x)*(x) )

struct pt {
    tint x, y, z;
    pt(tint xx=0.0, tint yy=0.0, tint zz=0.0) {
        x=xx; y=yy; z=zz;
    }
};

pt operator-(const pt &p1, const pt &p2) {
    return pt(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

pt operator+(const pt &p1, const pt &p2) {
    return pt(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
}

pt operator*(const pt &p, const double &c) {
    return pt(p.x*c, p.y*c, p.z*c);
}

tint norm2(const pt &p) {
    return SQ(p.x) + SQ(p.y) + SQ(p.z);
}

struct node {
    pt p, v;
} n[64];

struct edge {
    int a, b;
    pt p, v;
    bool used;
} m[2048];

struct event {
    double time;
    int u, v;
} e[4194304];

bool operator<(const event &e1, const event &e2) {
    return e1.time < e2.time;
}

tint TIME;
int RES, o[2048], N, M, f[64];

bool compare(const int &a, const int &b) {
    return norm2(m[a].p + m[a].v*TIME) < norm2(m[b].p + m[b].v*TIME);
}

int getf(int cur) {
    if (f[cur] != cur) f[cur] = getf(f[cur]);
    return f[cur];
}

void calc(double time) {
    TIME = time;
    sort(o, o+M, compare);
    for (int i=0; i<N; i++) f[i] = i;

    bool FLAG = false;
    for (int i=0; i<M; i++) {
        if (getf(m[o[i]].a) != getf(m[o[i]].b)) {
            f[getf(m[o[i]].a)] = getf(m[o[i]].b);
            if (!m[o[i]].used) FLAG = true;
            m[o[i]].used = true;
        } else m[o[i]].used = false;
    }
    if (FLAG) RES++;
}

int main() {
    int i, j, E, CASE;
    tint a, b, c, tmp;

    CASE = 1;
    while (cin >> N) {
        for (i=0; i<N; i++) cin >> n[i].p.x >> n[i].p.y >> n[i].p.z >> n[i].v.x >> n[i].v.y >> n[i].v.z;

        M = 0;
        for (i=0; i<N; i++) for (j=i+1; j<N; j++) {
            m[M].a = i; m[M].b = j;
            m[M].p = n[i].p-n[j].p;
            m[M].v = n[i].v-n[j].v;
            m[M].used = false;
            o[M] = M++;
        }

        E = 0;
        for (i=0; i<M; i++) for (j=i+1; j<M; j++) {
            a = norm2(m[i].v) - norm2(m[j].v);
            b = 2.0*(m[i].p.x*m[i].v.x + m[i].p.y*m[i].v.y + m[i].p.z*m[i].v.z - m[j].p.x*m[j].v.x - m[j].p.y*m[j].v.y - m[j].p.z*m[j].v.z);
            c = norm2(m[i].p) - norm2(m[j].p);
            if (abs(a) < EPS) {
                if (abs(b) > EPS) {
                    e[E].time = -c/b;
                    if(b*(e[E].time+DT) + c > 0.0) {e[E].u = j; e[E].v = i;}
                    else {e[E].u = i; e[E].v = j;}
                    E++;
                }
            } else {
                tmp = SQ(b)-4.0*a*c;
                if (tmp > EPS) {
                    e[E].time = (-b-sqrt(tmp))/(2.0*a);
                    if(a*SQ(e[E].time+DT) + b*(e[E].time+DT) + c > 0.0) {e[E].u = j; e[E].v = i;}
                    else {e[E].u = i; e[E].v = j;}
                    E++;

                    e[E].time = (-b+sqrt(tmp))/(2.0*a);
                    if(a*SQ(e[E].time+DT) + b*(e[E].time+DT) + c > 0.0) {e[E].u = j; e[E].v = i;}
                    else {e[E].u = i; e[E].v = j;}
                    E++;
                }
            }
        }
        sort(e, e+E);

        RES = 0; calc(0.0);
        for (i=0; i<E; i++) {
            if (e[i].time < 0.0) continue;
//            cout << "at time " << e[i].time << " edge " << e[i].u << " becomes smaller than edge " << e[i].v << endl;
            if (m[e[i].u].used^m[e[i].v].used) calc(e[i].time+DT);
        }
        cout << "Case " << CASE++ << ": " << RES << endl;
    }

    return 0;
}
