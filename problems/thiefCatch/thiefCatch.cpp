#include <iostream>

using namespace std;

int T;
int N, M, R, C, L;

int visited[50][50];

int MAP[50][50];
int MAP2[50][50];

int moveRows[4] = { -1, 0, 1, 0 };
int moveCols[4] = { 0, 1, 0, -1 };

int block[7] = { 15,5, 10 ,3 ,6, 12, 9 };

bool isRange(int rows, int cols) {
	if (rows < 0 || cols < 0 || rows >= N || cols >= M)
		return false;
	return true;
}

bool isPath(int rows, int cols, int direc) {
	if (direc == 0) {
		if (MAP[rows][cols] & (1 << 2))
			return true;
	}
	else if (direc == 1) {
		if (MAP[rows][cols] & (1 << 3))
			return true;
	}
	else if (direc == 2) {
		if (MAP[rows][cols] & (1 << 0))
			return true;
	}
	else if (direc == 3) {
		if (MAP[rows][cols] & (1 << 1))
			return true;
	}

	return false;
}

void solve(int rows, int cols, int depth) {
	if (depth == L) {
		MAP2[rows][cols] = 1;
		return;
	}

	int current = MAP[rows][cols];
	visited[rows][cols] = true;
	MAP2[rows][cols] = 1;

	for (int i = 0; i < 4; i++) {
		if (current & (1 << i)) {
			int nextRows = rows + moveRows[i];
			int nextCols = cols + moveCols[i];
			if (isRange(nextRows, nextCols) && !visited[nextRows][nextCols] && isPath(nextRows, nextCols, i)) {
				solve(nextRows, nextCols, depth + 1);
			}
		}
	}

	visited[rows][cols] = false;

}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);

		for(int i=0; i<N; i++)
			for (int j = 0; j < M; j++) {
				scanf("%d", &MAP[i][j]);
				if (MAP[i][j] == 1)
					MAP[i][j] = block[0];
				else if (MAP[i][j] == 2)
					MAP[i][j] = block[1];
				else if (MAP[i][j] == 3)
					MAP[i][j] = block[2];
				else if (MAP[i][j] == 4)
					MAP[i][j] = block[3];
				else if (MAP[i][j] == 5)
					MAP[i][j] = block[4];
				else if (MAP[i][j] == 6)
					MAP[i][j] = block[5];
				else if (MAP[i][j] == 7)
					MAP[i][j] = block[6];
				MAP2[i][j] = 0;
				visited[i][j] = false;
			}

		solve(R, C, 1);
		int count = 0;

		for(int i=0; i<N; i++)
			for (int j = 0; j < M; j++) {
				if (MAP2[i][j] == 1)
					count++;
			}
		printf("#%d %d\n", tc, count);
		count = 0;
	}
	return 0;
}
