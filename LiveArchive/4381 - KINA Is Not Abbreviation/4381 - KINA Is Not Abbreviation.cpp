#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
using namespace std;

typedef unsigned int HASH;

string pl;
map<string, int> w;
vector<string> invw;
vector<int> p;

void addword(string s) {
   if (w.find(s) == w.end()) {
		w[s] = invw.size();
		invw.push_back(s);
	}
	p.push_back(w[s]);
	pl += s[0];
}

HASH dohash(string s) {
	HASH RES = 5381U;
   for (int i=0; i<s.size(); i++) {
		RES = RES*33U + s[i]-'a';
	}
	return RES;
}

string UPPER(string s) {
	string RES = "";
   for (int i=0; i<s.size(); i++) {
		RES += s[i]+'A'-'a';
	}
	return RES;
}

int main() {
    
    int i, j, BEST, BESTPOS, BESTLEN, tmpi, len[2048];
    string tmp;
    char input[4096];
    bool flag;
    HASH htp[2048], htpl[2048];
    map<HASH, bool> invalid, used;
    map<HASH, HASH> corr;
    map<HASH, int> cant;
    map<HASH, int> pos;
    map<HASH, int>::iterator it;
    
    flag = true;
    while (flag) {
        
        invw.clear(); w.clear(); pl = ""; p.clear();
        while (flag) {
        	cin.getline(input, 4096);
        	flag = cin.eof();
        	if (strcmp(input, "") == 0) break;

        	tmp = "";
        	for (i=0; input[i]!='\0'; i++) {
        		if (input[i] >= 'A' && input[i] <= 'Z') input[i] = input[i]-'A'+'a';
        		if (input[i] >= 'a' && input[i] <= 'z') {
        			tmp += input[i];
        		} else if (tmp != "") {
        			addword(tmp);
        			tmp = "";
        		}
        	}
        	if (tmp != "") addword(tmp);
        }
        
        used.clear();
        for (i=0; i<invw.size(); i++) used[dohash(invw[i])] = true;
        
        len[0] = 0;
        for (i=0; i<p.size(); i++) {
        	len[i+1] = len[i] + invw[p[i]].size();
        	htpl[i] = htp[i] = 5381U;
        }
        
        BEST = 0; BESTPOS = -1; BESTLEN = -1;
        for (i=1; i<=p.size(); i++) {
        	invalid.clear(); corr.clear(); cant.clear(); pos.clear();
           for (j=0; j<=p.size()-i; j++) {
        		htpl[j] = htpl[j]*33U + pl[j+i-1]-'a';
        		htp[j] = htp[j]*2097 + p[j+i-1];
        
        		if (invalid.find(htpl[j]) == invalid.end() && used.find(htpl[j]) == used.end()) {
        		   if (corr.find(htpl[j]) == corr.end()) corr[htpl[j]] = htp[j];
        
        			if (corr[htpl[j]] != htp[j]) invalid[htpl[j]] = true;
        			else {
        				if (pos.find(htpl[j]) == pos.end()) {
        					cant[htpl[j]] = 1;
        					pos[htpl[j]] = j+i;
        				} else if (j >= pos[htpl[j]]) {
        					cant[htpl[j]]++;
        					pos[htpl[j]] = j+i;
        				}
        			}
        		}
        	}
        
        	for (it=cant.begin(); it!=cant.end(); it++) {
        		if (invalid.find(it->first) == invalid.end()) {
        			tmpi = (it->second - 1)*(len[pos[it->first]] - len[pos[it->first]-i] - i) - i;
        			if (tmpi > BEST) {
        				BEST = tmpi;
        				BESTPOS = pos[it->first];
        				BESTLEN = i;
        			}
        		}
        	}
        }
        cout << BEST << endl;
        if (BEST > 0) cout << UPPER(pl.substr(BESTPOS-BESTLEN, BESTLEN)) << endl;
        
        if (flag) cout << endl;
    }

    return 0;
}
