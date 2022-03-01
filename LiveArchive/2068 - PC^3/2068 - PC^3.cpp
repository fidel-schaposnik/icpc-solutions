#include <iostream>
using namespace std;

struct team {
	int score;
	bool problems[20];
};

int main() {

int N, P, T, S;
int problems[20];
team teams[301];
int i, j, curteam, temp1, temp2, problem, max, count;

cin >> N;
cin >> P;
cin >> T;
cin >> S;

do {

for (i=0; i<20; i++) {
	problems[i] = 0;
}

for (i=0; i<P; i++) {
	cin >> problems[i];
}

for (i=0; i<301; i++) {
	teams[i].score = 0;
	for (j=0; j<20; j++) {
		teams[i].problems[j] = 0;
	}
}

for (i=0; i<S; i++) {
	cin >> curteam;
	cin >> problem;
	cin >> temp1;
	cin >> temp2;
	if (temp2 == 0 && teams[curteam].problems[problem-1] == 0) {
		teams[curteam].score += problems[problem-1];
		teams[curteam].problems[problem-1] = 1;
	}
}

max=count=0;
for (i=1; i<T+1; i++) {
	if (teams[i].score > max) {max = teams[i].score; count = 1;}
	else if (teams[i].score == max) {count++;}
}

cout << "Contest " << N << " Winner:";

for (i=1; i<T+1; i++) {
	if (teams[i].score == max) {
		cout << " Team " << i;
		count--;
		if (count != 0) {cout << " and";}
	}
}

cout << endl;

cin >> N;
cin >> P;
cin >> T;
cin >> S;

} while (N!=0 || P!=0 || T!=0 || S!=0);

return 0;
}
