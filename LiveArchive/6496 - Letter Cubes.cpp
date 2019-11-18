#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int cur[6], used;
bool inv[26][26];
vector<int> v;
map<int, pair<int, int> > vv;

void dfs(int pos, int cant) {
    int i, mask;

    if (pos < 26) {
        dfs(pos+1, cant);
        if ((used&(1<<pos)) && cant < 6) {
            for (i=0; i<cant; i++) if (inv[pos][cur[i]]) break;
            if (i == cant) {
                cur[cant] = pos;
                dfs(pos+1, cant+1);
            }
        }
    } else if (cant == 6) {
        mask = 0;
        for (i=0; i<6; i++) mask ^= (1<<cur[i]);
        v.push_back(mask);
    }
}

string tos(int mask) {
    string res = "";
    for (int k=0; k<26; k++) if (mask&(1<<k)) res += (char)(k+'A');
    return res;
}

int main() {
    int N, i, j, k;
    char tmp, w[5];
    bool flag;
    string m[4];

    while (cin >> N && N) {
        cin >> tmp;

        memset(inv, false, sizeof(inv));
        used = 0; if (tmp != '-') used |= 1<<(tmp-'A');
        for (i=0; i<N; i++) {
            cin >> w;
            for (j=0; w[j]!='\0'; j++) used |= 1<<(w[j]-'A');
            for (j=0; w[j]!='\0'; j++) for (k=0; w[k]!='\0'; k++) {
                if (j == k) continue;
                inv[w[j]-'A'][w[k]-'A'] = true;
            }
        }

        v.clear(); dfs(0, 0);

        flag = false;
        if (w[2] == '\0') {
            for (i=0; !flag && i<(int)v.size(); i++) for (j=i+1; !flag && j<(int)v.size(); j++) if ((v[i]^v[j]) == used) flag = true;
            i--; j--;
            m[0] = tos(v[i]); m[1] = tos(v[j]);
            sort(m, m+2);
            cout << m[0] << ' ' << m[1] << endl;
        } else if (w[3] == '\0') {
            vv.clear();
            for (i=0; i<(int)v.size(); i++) for (j=i+1; j<(int)v.size(); j++) if (!(v[i]&v[j])) vv[v[i]^v[j]] = make_pair(v[i], v[j]);
            for (i=0; i<(int)v.size(); i++) if (vv.find(used^v[i]) != vv.end()) break;
            m[0] = tos(v[i]); m[1] = tos(vv[used^v[i]].first); m[2] = tos(vv[used^v[i]].second);
            sort(m, m+3);
            cout << m[0] << ' ' << m[1] << ' ' << m[2] << endl;
        } else {
            vv.clear();
            for (i=0; !flag && i<(int)v.size(); i++) for (j=i+1; !flag && j<(int)v.size(); j++) if (!(v[i]&v[j])) {
                if (vv.find(used^v[i]^v[j]) == vv.end()) vv[v[i]^v[j]] = make_pair(v[i], v[j]);
                else flag = true;
            }
            i--; j--;
            m[0] = tos(v[i]); m[1] = tos(v[j]); m[2] = tos(vv[used^v[i]^v[j]].first); m[3] = tos(vv[used^v[i]^v[j]].second);
            sort(m, m+4);
            cout << m[0] << ' ' << m[1] << ' ' << m[2] << ' ' << m[3] << endl;
        }
    }

    return 0;
}
