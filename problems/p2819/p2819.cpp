#include <iostream>
#define MAX 10000000
#define UP    0
#define LEFT  1
#define DOWN  2
#define RIGHT 3

using namespace std;

int T;

int map[4][4];
int movey[4] = { -1, 0, 1, 0 };
int movex[4] = { 0, 1, 0, -1 };

bool memo[MAX];

void init() {
	for (int i = 0; i < MAX; i++)
		memo[i] = false;
}

bool isRange(int row, int col) {
	if (row < 0 || col < 0)
		return false;
	if (row >= 4 || col >= 4)
		return false;
	return true;
}

int pow(int a, int x) {
	int sum = 1;
	for (int i = 0; i < x; i++)
		sum *= a;
	return sum;
}

int getCount(int y, int x, int currNum, int remain) {
	int decimal = (6 - remain);
	currNum += map[y][x] * pow(10, decimal);

	if (remain == 0) {
		if (!memo[currNum]) {
			memo[currNum] = true;
			return 1;
		}
		return 0;
	}

	int sum = 0;

	for (int d = 0; d < 4; d++) {
		int nextY = y + movey[d];
		int nextX = x + movex[d];
		if (isRange(nextY, nextX))
			sum += getCount(nextY, nextX, currNum, remain - 1);
	}

	return sum;
}

int solve() {
	int sum = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			sum += getCount(i, j, 0, 6);
	return sum;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				scanf("%d", &map[i][j]);
		init();
		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
