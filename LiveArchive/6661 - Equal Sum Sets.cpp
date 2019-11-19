#include <iostream>
using namespace std;

int RES;

void dfs(int cur, int left, int sum) {
    if (cur > 0) {
        dfs(cur-1, left, sum);
        if (left && sum >= cur) dfs(cur-1, left-1, sum-cur);
    } else if (sum == 0 && left == 0) RES++;
}

int main() {
    int N, K, S;

    while (cin >> N >> K >> S && (N || K || S)) {
        RES = 0; dfs(N, K, S);
        cout << RES << endl;
    }

    return 0;
}
