#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define MAX 1000003

typedef int state;
typedef int dist;

int bc[5][5] = {
{0,7,8,9,0},
{9,1,2,3,4},
{3,4,5,6,7},
{6,7,8,9,1},
{0,1,2,3,0}
};

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

vector< pair<state, dist> > d[MAX];
set< pair<dist, state> > s;

state m2s(int m[10]) {
    state tmp = 0;
    for (int i=1; i<=9; i++) tmp = tmp*10+m[i];
    return tmp;
}

void s2m(state st, int m[10]) {
    for (int i=9; i>=1; i--) {
        m[i] = st%10;
        st /= 10;
    }
}

void insert(state st, dist di) {
	int cur = st%MAX, i;
	for (i=0; i<(int)d[cur].size(); i++) if (d[cur][i].first == st) break;
	if (i<(int)d[cur].size()) d[cur][i].second = di;
	else d[cur].push_back(make_pair(st, di));
}

dist get(state st) {
	int cur = st%MAX;
	for (int i=0; i<(int)d[cur].size(); i++) if (d[cur][i].first == st) return d[cur][i].second;
	return -1;
}

int main() {
    int COST[2], m[10], i, x, y;
    state cur, next, start, end;
	dist curd, nextd;

    while (cin >> COST[0] >> COST[1] && (COST[0] || COST[1])) {
        for (i=1; i<=9; i++) cin >> m[i];
        start = m2s(m);
        for (i=1; i<=9; i++) cin >> m[i];
        end = m2s(m);
        
        for (i=0; i<MAX; i++) d[i].clear(); s.clear();
    
        insert(start, 0); s.insert(make_pair(0, start));
        while (!s.empty()) {
            cur = s.begin()->second; curd = s.begin()->first; s.erase(s.begin());

            if (cur == end) break;
    
            s2m(cur, m);
            for (i=1; i<=9; i++) if (!m[i]) break;
            x = (i-1)%3+1; y = (i-1)/3+1;
    
            for (int j=0; j<4; j++) {
                swap(m[bc[y+dy[j]][x+dx[j]]], m[i]);
                next = m2s(m);
                swap(m[bc[y+dy[j]][x+dx[j]]], m[i]);
    
    			nextd = get(next);
                if (nextd == -1) {
                    insert(next, curd+COST[j/2]);
                    s.insert(make_pair(curd+COST[j/2], next));
                } else {
                    if (nextd > curd+COST[j/2]) {
                        s.erase(make_pair(nextd, next));
                        s.insert(make_pair(curd+COST[j/2], next));
                        insert(next, curd+COST[j/2]);
                    }
                }
            }
        }
        cout << get(end) << endl;
    }

    return 0;
}
