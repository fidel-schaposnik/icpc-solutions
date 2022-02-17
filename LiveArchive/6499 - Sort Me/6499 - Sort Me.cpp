#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int v[256];

bool cmp(const string &s1, const string &s2) {
    for (int i=0; i<(int)min(s1.size(), s2.size()); i++) if (s1[i] != s2[i]) return v[s1[i]] < v[s2[i]];
    return s1.size() < s2.size();
}

int main() {
    int N, i, t;
    string n[32], o;

    t = 1;
    while (cin >> N && N) {
        cin >> o;
        for (i=0; i<26; i++) v[o[i]] = i;
        for (i=0; i<N; i++) cin >> n[i];

        sort(n, n+N, cmp);
        cout << "year " << t++ << endl;
        for (i=0; i<N; i++) cout << n[i] << endl;
    }

    return 0;
}
