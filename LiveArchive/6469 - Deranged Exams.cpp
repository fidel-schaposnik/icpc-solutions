#include <iostream>
#include <cstring>
using namespace std;

int N, K;
long long cant[1<<17];

long long _cant(int mask) {
    int i, cur = 0;
    if (cant[mask] == -1LL) {
        for (i=0; i<N; i++) if ( mask&(1<<i) ) cur++;
    
        cant[mask] = 0LL;
        for (i=0; i<N; i++) if ( (mask&(1<<i)) && (cur > K || i+1!=cur) ) cant[mask] += _cant(mask^(1<<i));
    }
    return cant[mask];
}

int main() {
    int T, t, ID;

    cin >> T;
    for (t=0; t<T; t++) {
        cin >> ID >> N >> K;

        memset(cant, -1LL, sizeof(cant)); cant[0] = 1LL;
        cout << ID << ' ' << _cant((1<<N)-1) << endl;
    }

    return 0;
}
