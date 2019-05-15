#include <iostream>

using namespace std;
int T, N;
int MAP[20][20];

int path[200];
int pathCount = 0;

int direcMemo[4];

int MAX = -1;
int movey[4] = { -1, -1, 1, 1 }; //leftup, rightup, leftdown, rightdown
int movex[4] = { -1, 1, -1, 1 };

int starty;
int startx;
int startdirec;
int startdirec2;
int startdirec3;

bool isRange(int rows, int cols) {
	if (rows < 0 || cols <0 || rows>(N - 1) || cols>(N - 1))
		return false;
	return true;
}

bool isMove(int rows, int cols, int visitCount) {
	if (rows == starty && cols == startx)
		return true;

	for (int i = 0; i < visitCount; i++) {
		if (path[i] == MAP[rows][cols])
				return false;
	}
	return true;
}

bool isPossible(int direc, int count) {
	int realcount = count + 1;

	if (realcount < 2)
		return true;
	else {
		if (direcMemo[realcount - 2] == direc)
			return false;
	}
}

void tourStart(int rows, int cols, bool visited[20][20], int direc, int direcCount, int visitCount) {
	if (direc == -1) {
		starty = rows;
		startx = cols;
	}
	
	if (direcCount == 1) {
		startdirec3 = direc;
	}
	if (direcCount == 3) {
		if (startdirec3 == direc)
			return;
	}
	if (direcCount == 2) {
		if (startdirec == direc) 
			return;
		startdirec2 = direc;
	}
	if (direcCount == 4) {
		if (startdirec2 == direc)
			return;
	}
	
	if (direcCount > 4)
		return;

	if (direcCount > 2 && direcCount < 5 && rows == starty && cols == startx) {
		visitCount--;
		if (visitCount > MAX)
			MAX = visitCount;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (direc == -1) {
			startdirec = i;
		}
		if (direc + i == 3) // 반대방향인 경우
			continue;
		int nextrows = rows + movey[i];
		int nextcols = cols + movex[i];

		if (isRange(nextrows, nextcols) && isMove(nextrows, nextcols, visitCount)) {
			if (visited[nextrows][nextcols] == true) {
				continue;
			}
			else {
				visited[nextrows][nextcols] = true;
				path[visitCount] = MAP[nextrows][nextcols];

				if (direc != i) {
					//if (isPossible(i, direcCount)) {
					//	direcMemo[direcCount+1] = i;
						tourStart(nextrows, nextcols, visited, i, direcCount + 1, visitCount + 1);
						//direcMemo[direcCount+1] = -1;
					//}
				}
				else {
					tourStart(nextrows, nextcols, visited,  i, direcCount, visitCount + 1);
				}

				visited[nextrows][nextcols] = false;
				path[visitCount] = -1;
			}
		}
	}
}

void solve() {
	bool visited[20][20] = { false };
	for (int i = 0; i < N/2+2; i++) {
		for (int j = 0; j < N/2+2; j++) {
			path[0] = MAP[i][j];
			tourStart(i, j, visited, -1, -1, 1);
		}
	}
}

int main()
{
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &MAP[i][j]);
			}
		}
		solve();
		printf("#%d %d\n", tc, MAX);
		MAX = -1;
	}

	return 0;
}
