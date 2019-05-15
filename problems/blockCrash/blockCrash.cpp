#include <iostream>
using namespace std;
int T, N, W, H;
int MAP[15][12];
int MIN = 987654321;
int movey[4] = { -1, 0, 1, 0 };
int movex[4] = { 0, 1, 0, -1 };

void cloneStone(int m[15][12], const int m2[][12]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			m[i][j] = m2[i][j];
		}
	}
}
bool isRange(const int& y, const int& x) {
	if (y < 0 || x < 0 || y >= H || x >= W)
		return false;
	return true;
}
void breakStone(int m[15][12], const int& y, const int& x) {
	int stone = m[y][x];
	m[y][x] = 0;
	for (int j = 1; j < stone; j++) {
		for (int i = 0; i < 4; i++) {
			int nexty = y + (movey[i] * j);
			int nextx = x + (movex[i] * j);
			if (isRange(nexty, nextx)) {
				if (m[nexty][nextx] <= 1)
					m[nexty][nextx] = 0;
				else
					breakStone(m, nexty, nextx);
			}
		}
	}
}

void findStone(int m[15][12], const int& x) {
	for (int i = 0; i < H; i++) {
		if (m[i][x] != 0) {
			breakStone(m, i, x);
			break;
		}
	}
}

void sortStone(int m[15][12]) {
	int idx;
	int flag = false;
	for (int i = 0; i < W; i++) {
		flag = false;
		for (int j = H - 1; j >= 0; j--) {
			if (m[j][i] == 0 && flag == false) {
				idx = j;
				flag = true;
			}
			else if (m[j][i] != 0 && flag == true) {
				m[idx][i] = m[j][i];
				m[j][i] = 0;
				flag = false;
				j = idx;
			}
		}
	}
}
void sortStone2(int stoneclone[15][12]) {
	int locate[15];
	int count = 0;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (stoneclone[j][i] != 0) {
				locate[count] = stoneclone[j][i];
				stoneclone[j][i] = 0;
				count++;
			}
		}
		for (int j = 0; j < count; j++) {
			stoneclone[H - 1 - j][i] = locate[count - 1 - j];
		}
		count = 0;
	}
}
int calStone(const int m[15][12]) {
	int result = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (m[i][j] != 0)
				result++;
		}
	}
	return result;
}

int allbreakStone(int m[15][12], const int& x, const int& turn) {
	if (turn == N) {
		return calStone(m);
	}
	int result;

	int currentMAP[15][12];

	findStone(m, x);
	//breakStone(m, y, x);
	sortStone2(m);

	for (int i = 0; i < W; i++) {
		cloneStone(currentMAP, m);
		result = allbreakStone(currentMAP, i, turn + 1);
		if (MIN > result)
			MIN = result;
	}

	return MIN;
}

int solve() {
	int result;
	int currentMAP[15][12];
	for (int i = 0; i < W; i++) {
		cloneStone(currentMAP, MAP);
		result = allbreakStone(currentMAP, i, 0);
	}
	return MIN;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &W, &H);
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &MAP[i][j]);
			}
		}
		printf("#%d %d\n", tc, solve());
		MIN = 987654321;
	}
	return 0;
}
