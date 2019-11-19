#include <cstdio>
using namespace std;

#define MAXN 131072
#define SIGN(x) ( (x)<0LL ? -1 : 1 )

struct pt {
	long long x, y;
	pt(long long xx=0LL, long long yy=0LL) {
		x = xx; y = yy;
	}
};

pt operator-(const pt &p1, const pt &p2) {
	return pt(p1.x-p2.x, p1.y-p2.y);
}

long long operator^(const pt &p1, const pt &p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool operator==(const pt &p1, const pt &p2) {
	return p1.x==p2.x && p1.y==p2.y;
}

struct seg {
	pt p1, p2;
	seg(pt p1i=pt(0LL,0LL), pt p2i=pt(0LL,0LL)) {
		p1=p1i; p2=p2i;
	}
} n[MAXN];

bool inter(const seg &s1, const seg &s2) {
	if (((s1.p2-s1.p1)^(s2.p1-s1.p1)) == 0LL) return true;
	else if (((s1.p2-s1.p1)^(s2.p2-s1.p1)) == 0LL) return false;
	else if (SIGN((s1.p2-s1.p1)^(s2.p1-s1.p1)) != SIGN((s1.p2-s1.p1)^(s2.p2-s1.p1))) {
		if (s2.p1.x == s2.p2.x && (s1.p2.x*s2.p1.x)%s1.p2.x == 0LL && (s1.p2.y*s2.p1.x)%s1.p2.x == 0LL) return true;
		else if (s2.p1.y == s2.p2.y && (s1.p2.x*s2.p1.y)%s1.p2.y == 0LL && (s1.p2.y*s2.p1.y)%s1.p2.y == 0LL) return true;
		else return false;
	} else return false;
}

int main() {
	int T, t, N, i, RES;
	long long x, y, tmp;
	char tmpc;
	
	scanf("%d", &T);
	for (t=0; t<T; t++) {
		scanf("%d", &N);
		
		x = y = 0LL;
		for (i=0; i<N; i++) {
			scanf("%I64d %c", &tmp, &tmpc);
			if (tmpc == 'B') { n[i] = seg(pt(x,y),pt(x+tmp,y)); x += tmp; }
			else if (tmpc == 'W') { n[i] = seg(pt(x,y),pt(x,y+tmp)); y += tmp; }
		}
		
		if (x != 0LL && y != 0LL) {
			RES = 0;
			for (i=0; i<N; i++) if (inter(seg(pt(0LL,0LL),pt(x,y)),n[i])) RES++;
			printf("%d\n", RES);
		} else printf("%d\n", x+y);
	}

	return 0;
}
