#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define R 6370.0
#define EPS 1E-12
#define INF 1E12

typedef double tint;

const tint pi = 2.0*acos(0.0);

#define SQ(x) ( (x)*(x) )

struct pt {
    tint x, y ,z;
    pt(tint xx=0.0, tint yy=0.0, tint zz=0.0) {
        x=xx; y=yy; z=zz;
    }
} o[32], n[768];

pt operator^(const pt &p1, const pt &p2) {
    return pt(p1.y*p2.z - p1.z*p2.y, -p1.x*p2.z + p1.z*p2.x, p1.x*p2.y - p1.y*p2.x);
}

tint operator*(const pt &p1, const pt &p2) {
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

pt operator+(const pt &p1, const pt &p2) {
    return pt(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);
}

pt operator/(const pt &p, const tint &c) {
    return pt(p.x/c, p.y/c, p.z/c);
}

pt operator*(const tint &c, const pt &p) {
    return pt(p.x*c, p.y*c, p.z*c);
}

pt operator*(const pt &p, const tint &c) {
    return pt(p.x*c, p.y*c, p.z*c);
}

tint norm2(const pt &p) {
    return p*p;
}

tint norm(const pt &p) {
    return sqrt(norm2(p));
}

struct plane {
    pt n;
    tint d;
    plane(pt normal=pt(0.0,0.0), tint dd=0.0) {
        n=normal; d=dd;
    }
} p[32];

struct line {
    pt p, v;
    line(pt point=pt(0.0,0.0), pt dir=pt(0.0,0.0)) {
        p=point; v=dir;
    }
};

struct spt {
    tint lat, lon;
    spt(tint latitude=0.0, tint longitude=0.0) {
        lat = latitude; lon = longitude;
    }
} a[32];

void gaussjordan(tint **A, int M, int N) {
    int i, j, k, maxi; tint tmp;

    for (i=0; i<M; i++) {
        maxi = i;
        for (k=i+1; k<M; k++) if (abs(A[k][i]) > abs(A[maxi][i])) maxi = k;

        for (j=0; j<N; j++) swap(A[i][j], A[maxi][j]);

        for (j=0; j<N; j++) if (j != i) A[i][j] /= A[i][i];
        A[i][i] = 1.0;

        for (k=0; k<M; k++) if (k != i) {
            for (j=i+1; j<N; j++) A[k][j] -= A[k][i]*A[i][j];
            A[k][i] = 0;
        }
    }
}

line inter(const plane &p1, const plane &p2) {
    tint m[5][6], *mm[5];
    pt p, v = p1.n^p2.n;
    for (int i=0; i<5; i++) mm[i] = m[i];
    if (norm2(v) > EPS) {
        v = v/norm(v);
        for (int i=0; i<5; i++) for (int j=0; j<6; j++) m[i][j] = 0.0;
        m[0][0] = m[1][1] = m[2][2] = 2.0;
        m[0][3] = m[3][0] = p1.n.x; m[1][3] = m[3][1] = p1.n.y; m[2][3] = m[3][2] = p1.n.z;
        m[0][4] = m[4][0] = p2.n.x; m[1][4] = m[4][1] = p2.n.y; m[2][4] = m[4][2] = p2.n.z;
        m[3][5] = -p1.d; m[4][5] = -p2.d;
        gaussjordan(mm, 5, 6);
        p = pt(m[0][5], m[1][5], m[2][5]);
    }
    return line(p, v);
}

int N, A;
tint D, r, d[768][768], dd[32][32];

pt arc(const pt &u, const pt &v, const tint &t) {
    return u*cos(t) + v*sin(t);
}

bool check(const pt &u, const pt &v, tint s, tint e) {
    int cur;
    for (cur=0; cur<A; cur++) if (arc(u, v, s+EPS)*o[cur] > r) break;
    if (cur == A) return false;
    else if (e-s < EPS || arc(u, v, e-EPS)*o[cur] > r) return true;
    else {
        tint left=s, right=e, mid;
        while (right-left > EPS) {
            mid = (left+right)/2.0;
            if (arc(u, v, mid)*o[cur] > r) left = mid;
            else right = mid;
        }
        return check(u, v, (left+right)/2.0, e);
    }
}

int main() {
    int i, j, dlon, dlat, source, destination, Q, CASE=1;
    tint s, e, m, alpha, tmp;
    line tmpl;
    pt tmppt, v;

    while (cin >> A >> D) {
        r = R*cos(D/R);
        for (i=0; i<A; i++) {
            cin >> dlon >> dlat;
            a[i] = spt(pi*dlat/180.0, pi*dlon/180.0);
            o[i] = pt(cos(a[i].lat)*cos(a[i].lon), cos(a[i].lat)*sin(a[i].lon), sin(a[i].lat));
            p[i] = plane(o[i], -r);
            n[i] = R*o[i];
        }
    
        N = A;
        for (i=0; i<A; i++) for (j=i+1; j<A; j++) {
            tmpl = inter(p[i], p[j]);
            if (norm2(tmpl.v) < EPS || norm(tmpl.p) > R) continue;
    
            s = 0.0; e = R;
            while (e-s > EPS) {
                m = (s+e)/2.0;
                if (norm(tmpl.p + m*tmpl.v) < R) s = m;
                else e = m;
            }
            n[N++] = tmpl.p + ((s+e)*tmpl.v)/2.0;
            n[N++] = tmpl.p + ((-s-e)*tmpl.v)/2.0;
        }

        for (i=0; i<N; i++) for (j=0; j<N; j++) d[i][j] = INF;
        for (i=0; i<N; i++) for (j=i+1; j<N; j++) {
            tmppt = n[i]^n[j];
            if (norm2(tmppt) < EPS) continue;
    
            alpha = acos(n[i]*n[j]/SQ(R));
            v = tmppt^n[i]; v = R*(v/norm(v));
            if (check(n[i], v, 0.0, alpha)) d[i][j] = d[j][i] = R*alpha;
        }
        for (int k=0; k<N; k++) for (i=0; i<N; i++) for (j=0; j<N; j++) if (d[i][k]+d[k][j] < d[i][j]) d[i][j] = d[i][k]+d[k][j];
    
        cin >> Q; cout << "Case " << CASE++ << ":" << endl;
        for (int q=0; q<Q; q++) {
            cin >> source >> destination >> tmp;
            for (i=0; i<A; i++) for (j=0; j<A; j++) {
                if (d[i][j] < tmp) dd[i][j] = d[i][j];
                else dd[i][j] = INF;
            }

            for (int k=0; k<A; k++) for (i=0; i<A; i++) for (j=0; j<A; j++) if (dd[i][k]+dd[k][j] < dd[i][j]) dd[i][j] = dd[i][k]+dd[k][j];
            if (dd[source-1][destination-1] < INF) printf("%.3lf\n", dd[source-1][destination-1]);
            else cout << "impossible" << endl;
        }
    }

    return 0;
}
