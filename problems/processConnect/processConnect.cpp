#include < iostream >
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;
int T, N;
int maxConnect = 0;
int minNonConnectCountOfMaxConnect = 12;
int minLength[13]; // index = core연결 수

class Map {
public:
	int cols[12]; //열정보
	int rows[12]; //행정보
	Map() {
		init();
	}
	void init() {
		for (int i = 0; i < 12; i++) {
			cols[i] = 0;
			rows[i] = 0;
		}
	}
	void set(int y, int x) {
		rows[y] |= (1 << x);
		cols[x] |= (1 << y);
	}
};

class Core {
public:
	int y_, x_;
	bool connect;
	Core() {
		connect = false;
	}
	void set(int y, int x) {
		y_ = y;
		x_ = x;
	}
};

Map map;
Core cores[12];
int coreCount = 0;
int bit = 0;

void init() {
	for (int i = 0; i < 13; i++)
		minLength[i] = 5000;
	for (int i = 0; i < N; i++)
		bit |= (1 << i);
	map.init();
	maxConnect = 0;
	coreCount = 0;
	minNonConnectCountOfMaxConnect = 12;
}

bool isPossible(const Map& m, int core, int direc) {
	if (cores[core].y_ == 0 || cores[core].y_ == N - 1 || cores[core].x_ == 0 || cores[core].x_ == N - 1)
		return false;

	if (direc == UP) {
		int cols = m.cols[cores[core].x_];
		int compare = bit >> (N - cores[core].y_);
		return !(compare & cols);
	}
	else if (direc == DOWN) {

		int cols = m.cols[cores[core].x_];
		int compare = bit << (cores[core].y_+1);
		return !(compare & cols);
	}
	else if (direc == LEFT) {
		int rows = m.rows[cores[core].y_];

		int compare = bit >> (N-cores[core].x_);
		return !(compare & rows);
	}
	else if (direc == RIGHT) {
		int rows = m.rows[cores[core].y_];
		int compare = bit << (cores[core].x_+1);
		return !(compare & rows);
	}
}

Map connect(Map m, int core, int direc, int& length) {

	if (direc == UP) {
		for (int i = 0; i < cores[core].y_; i++) {
			m.rows[i] |= (1 << cores[core].x_);
		}
		int add = bit >> (N - cores[core].y_);
		m.cols[cores[core].x_] |= add;
		length = cores[core].y_;
	}
	else if (direc == DOWN) {
		for (int i = N-1; i > cores[core].y_; i--) {
			m.rows[i] |= (1 << cores[core].x_);
		}
		int add = bit << (cores[core].y_ + 1);
		m.cols[cores[core].x_] |= add;
		length = N - cores[core].y_ - 1;
	}
	else if (direc == LEFT) {
		for (int i = 0; i < cores[core].x_; i++) {
			m.cols[i] |= (1 << cores[core].y_);
		}
		int add = bit >> (N - cores[core].x_);
		m.rows[cores[core].y_] |= add;
		length = cores[core].x_;
	}
	else if (direc == RIGHT) {
		for (int i = N-1; i > cores[core].x_; i--) {
			m.cols[i] |= (1 << cores[core].y_);
		}
		int add = bit << (cores[core].x_ + 1);
		m.rows[cores[core].y_] |= add;
		length = N - cores[core].x_ - 1;
	}

	return m;
}
void printMap(const Map& m) {
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (m.rows[j] & (1 << i))
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (m.cols[i] & (1 << j))
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}

}
void nextCoreTry(Map m, int currCore, int currLength, int connectCount, int nonConnectCount) {
	if (minNonConnectCountOfMaxConnect < nonConnectCount)
		return;
	if (currCore == coreCount) {
		//cout << endl;
		//printMap(m);
		if (minLength[connectCount] > currLength)
			minLength[connectCount] = currLength;
		if (minNonConnectCountOfMaxConnect > nonConnectCount) {
			minNonConnectCountOfMaxConnect = nonConnectCount;
		}
		if (maxConnect < connectCount)
			maxConnect = connectCount;
		return;
	}

	for (int i = 0; i < 4; i++) {
		//map에 0번쨰코어를 i방향으로 연결시킬수있니
		if (isPossible(m, currCore, i)) {
			int addLength;
			Map next = connect(m, currCore, i, addLength);

			nextCoreTry(next, currCore + 1, currLength + addLength, connectCount + 1, nonConnectCount);
		}

	}

	if (cores[currCore].y_ == 0 || cores[currCore].y_ == N - 1 || cores[currCore].x_ == 0 || cores[currCore].x_ == N - 1)
		nextCoreTry(m, currCore + 1, currLength, connectCount + 1, nonConnectCount);
	else
		nextCoreTry(m, currCore + 1, currLength, connectCount, nonConnectCount+1);

}
int solve() {
	int start = 0;

	for (int i = 0; i < 4; i++) {
		int currLength = 0;
		//map에 0번쨰코어를 i방향으로 연결시킬수있니
		if (isPossible(map, start, i)) {
			int addLength;
			Map next = connect(map, start, i, addLength);
			nextCoreTry(next, start + 1, currLength + addLength, 1, 0);
		}
	}

	if (cores[start].y_ == 0 || cores[start].y_ == N - 1 || cores[start].x_ == 0 || cores[start].x_ == N - 1)
		nextCoreTry(map, start + 1, 0, 1, 0);
	else
		nextCoreTry(map, start + 1, 0, 0, 1);

	return minLength[maxConnect];
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int tmp;
				scanf("%d", &tmp);
				if (tmp == 1) {
					map.set(i, j);
					cores[coreCount].set(i, j);
					coreCount++;
				}
			}
		}

		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
