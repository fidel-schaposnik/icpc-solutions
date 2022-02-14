#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int r[6];
string s[6], t[6];

int main() {
	int re, n;
	char buf[80];

	scanf("%d", &re);
	for (int ri = 1; ri <= re; ++ri) {
		scanf("%d", &n);
		for (int i = 0; i < 5; ++i) {
			s[i] = t[i] = "";
		}
		for (int i = 0; i < 6; ++i) {
			scanf("%s", buf);
			for (int j = 0; j < 5; ++j) {
				s[j] += buf[j];
			}
		}
		for (int i = 0; i < 6; ++i) {
			scanf("%s", buf);
			for (int j = 0; j < 5; ++j) {
				t[j] += buf[j];
			}
		}

		for (int i = 0; i < 5; ++i) {
			sort(s[i].begin(), s[i].end());
			sort(t[i].begin(), t[i].end());
			s[i].erase(set_intersection(s[i].begin(), s[i].end(), t[i].begin(), t[i].end(), s[i].begin()), s[i].end());
			s[i].erase(unique(s[i].begin(), s[i].end()), s[i].end());
			r[i] = s[i].length();
		}
		r[5] = 1;
		for (int i = 4; i >= 0; --i) {
			r[i] *= r[i + 1];
		}
//		cerr << r[0] << endl;

		--n;
		if (n >= r[0]) {
			puts("NO");
		} else {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < (int)s[i].length(); ++j) {
					if (n >= r[i + 1]) {
						n -= r[i + 1];
					} else {
						putchar(s[i][j]);
						break;
					}
				}
			}
			puts("");
		}
	}

	return 0;
}

