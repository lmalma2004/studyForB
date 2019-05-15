#include <iostream>

using namespace std;

int T;
int N, K;

int MAP[8][8];

int startNumber = 0;
int startCount = 0;

int startx[5];
int starty[5];

int movey[4] = { -1, 0, 1, 0 };
int movex[4] = { 0, 1, 0, -1 };

void findStartPoint() {
	int count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (MAP[i][j] == startNumber) {
				starty[count] = i;
				startx[count] = j;
				count++;
			}
		}
	startCount = count;
}


bool isRange(int rows, int cols) {
	if (rows < 0 || cols < 0 || rows >= N || cols >= N)
		return false;
	return true;
}

bool isPossible(int y, int x, int ny, int nx) {
	if (MAP[y][x] > MAP[ny][nx])
		return true;
	return false;
}

int longestPath(int currenty, int currentx, unsigned long long visited) {
	int max = 0;

	for (int i = 0; i < 4; i++) {
		int result = 1;
		int nexty = currenty + movey[i];
		int nextx = currentx + movex[i];

		if (isRange(nexty, nextx) && !(visited & (1 << (N*nexty + nextx)))
			&& isPossible(currenty, currentx, nexty, nextx)) {
			result += longestPath(nexty, nextx, visited | (1 << (N*nexty + nextx)));
		}

		if (max < result)
			max = result;
	}

	return max;
}
int longestPath2(int currenty, int currentx, bool visited[8][8]) {
	int max = 0;

	for (int i = 0; i < 4; i++) {
		int result = 1;
		int nexty = currenty + movey[i];
		int nextx = currentx + movex[i];

		if (isRange(nexty, nextx) && !visited[nexty][nextx]
			&& isPossible(currenty, currentx, nexty, nextx)) {
			visited[nexty][nextx] = true;
			result += longestPath2(nexty, nextx, visited);
			visited[nexty][nextx] = false;
		}

		if (max < result)
			max = result;
	}

	return max;
}
int solve() {
	bool visited2[8][8] = { false };
	unsigned long long visited = 0;
	int result;
	int result2;
	int max = 0;

	findStartPoint();

	for (int i = 0; i < startCount; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				for (int h = 0; h <= K; h++) {
					int temp = 0;

					if (j != starty[i] || k != startx[i]) {
						MAP[j][k] -= h;
						if (MAP[j][k] < 0) {
							temp = MAP[j][k];
							MAP[j][k] = 0;
						}
					}

					//result = longestPath(starty[i], startx[i], visited | (1 << (N*starty[i] + startx[i])));
					visited2[starty[i]][startx[i]] = true;
					result = longestPath2(starty[i], startx[i], visited2);
					visited2[starty[i]][startx[i]] = false;


					if (j != starty[i] || k != startx[i]) {
						if (temp != 0)
							MAP[j][k] = temp + h;
						else
							MAP[j][k] += h;
					}

					if (result > max)
						max = result;
				}
			}
		}
	}

	return max;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				scanf("%d", &MAP[i][j]);
				if (startNumber < MAP[i][j])
					startNumber = MAP[i][j];
			}

		printf("#%d %d\n", tc, solve());
		startNumber = 0;
	}

	return 0;
}
