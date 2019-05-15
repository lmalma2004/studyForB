#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int state[28];
unsigned int allPW[28];
int count_ = 0;
int T, N, K;

void printPW() {
	for (int i = 0; i < 28; i++)
		cout << allPW[i] << " ";
	cout << endl;
}
void init() {
	for (int i = 0; i < 28; i++) {
		state[i] = 0;
		allPW[i] = 0;
	}
	count_ = 0;
}

void eraseOverlap() {
	for (int i = 0; i < N - 1; i++) {
		if (allPW[i] == allPW[i + 1])
			allPW[i] = 0;
	}
}
unsigned int calPW(int slotstart, int rotateNumber) {
	unsigned int sum = 0;
	for (int i = 0; i < rotateNumber; i++) {
		if (slotstart + i == N)
			slotstart = -i;
		sum += state[slotstart + i] * pow(16, rotateNumber - i - 1);
	}
	return sum;
}

void pushPW(int currRotate, int rotateNumber) {
	int slotstart[4];
	for (int i = 0; i < 4; i++) {
		slotstart[i] = (rotateNumber)*i + currRotate;
		if (slotstart[i] == N)
			slotstart[i] = 0;

		allPW[count_++] = calPW(slotstart[i], rotateNumber);
	}

}
int compare(const void *a,const void *b) {
	if (*(unsigned int*)a < *(unsigned int*)b)
		return 1;
	else if (*(unsigned int*)a > *(unsigned int*)b)
		return -1;
	else
		return 0;
}
unsigned int solve() {
	int rotateNumber = N / 4;

	for (int i = 0; i <rotateNumber; i++) {
		pushPW(i, rotateNumber);
	}

	//printPW();
	qsort(allPW, 28, sizeof(allPW[0]), compare);
	//printPW();
	eraseOverlap();
	qsort(allPW, 28, sizeof(allPW[0]), compare);
	//printPW();

	return allPW[K - 1];
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
			scanf("%1x", &state[i]);

		printf("#%d %d\n", tc, solve());
		init();
	}

	return 0;
	
}
