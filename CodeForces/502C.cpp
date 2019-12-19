#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 131072

int p[MAXN], N;

int value(int size) {
	int cant = (N+size-1)/size;
	return size + cant;
}

void reverse(int a, int b) {
	for (int i=0; i<(b-a)/2; i++) {
		int tmp = p[a+i];
		p[a+i] = p[b-1-i];
		p[b-1-i] = tmp;
	}
}

void make_perm(int size) {
	int i;
	for (i=1; i<=N; i++) p[i-1] = i;
	for (i=0; i<N; i+=size) reverse(i,min(N,i+size));
	reverse(0,N);
}

int main() {
	scanf("%d", &N);

	if (N == 1) printf("1\n");
	else if (N == 2) printf("2 1\n");
	else if (N == 3) printf("1 2 3\n");
	else if (N == 4) printf("3 4 1 2\n");
	else {
		if (value(sqrt(N)) <= value(sqrt(N)-1) && value(sqrt(N)) <= value(sqrt(N)+1)) make_perm(sqrt(N));
		else if (value(sqrt(N)+1) <= value(sqrt(N)) && value(sqrt(N)+1) <= value(sqrt(N)-1)) make_perm(sqrt(N)+1);
		else if (value(sqrt(N)-1) <= value(sqrt(N)) && value(sqrt(N)-1) <= value(sqrt(N)+1)) make_perm(sqrt(N)-1);
		for (int i=0; i<N-1; i++) printf("%d ", p[i]);
		printf("%d\n", p[N-1]);
	}
	
	return 0;
}
