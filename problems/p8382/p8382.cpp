#include <iostream>
#include <queue>
#include <vector>
#define UP      0
#define LEFT   1
#define DOWN   2
#define RIGHT   3
#define NOTHING 4
using namespace std;

#include <iostream>
#include <queue>
#include <vector>
#define UP      0
#define LEFT   1
#define DOWN   2
#define RIGHT   3
#define NOTHING 4
using namespace std;

int moveX[4] = { -1, 0, 1, 0 };
int moveY[4] = { 0, 1, 0, -1 };

int T;
int x1, y1;
int x2, y2;

class State {
public:
	int x;
	int y;
	int moveCnt;
	int currDirec;
	State() {
		currDirec = NOTHING;
	}
	State(int x_, int y_, int mC, int cD) {
		x = x_;
		y = y_;
		moveCnt = mC;
		currDirec = cD;
	}
};

int getDistance(int x, int y) {
	return (x - x2)*(x - x2) + (y - y2)*(y - y2);
}

class compareState {
public:
	bool operator()(const State& s1, const State& s2) {
		if (s1.moveCnt == s2.moveCnt) {
			int distance1 = getDistance(s1.x, s1.y);
			int distance2 = getDistance(s2.x, s2.y);
			return distance1 > distance2;
		}
		return s1.moveCnt > s2.moveCnt;
	}
};

class PriorityQueue {
public:
	static const int MAX_SIZE = 10000;
	State heap[MAX_SIZE];
	int heapSize;
public:
	PriorityQueue() {
		heapSize = 0;
	}
	bool compare(int a, int b) {
		if (heap[a].moveCnt == heap[b].moveCnt) {
			int distance1 = getDistance(heap[a].x, heap[a].y);
			int distance2 = getDistance(heap[b].x, heap[b].y);
			return distance1 < distance2;
		}
		return heap[a].moveCnt < heap[b].moveCnt;
	}
public:
	void heapInit(void)
	{
		heapSize = 0;
	}

	void push(State state)
	{
		if (heapSize + 1 > MAX_SIZE)
			return;

		heap[heapSize] = state;

		int current = heapSize;
		while (current > 0 && compare(current, (current - 1) / 2))
		{
			State temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}

		heapSize = heapSize + 1;
	}

	void pop()
	{
		if (heapSize <= 0)
			return;
		heapSize = heapSize - 1;

		heap[0] = heap[heapSize];

		int current = 0;
		while (current * 2 + 1 < heapSize)
		{
			int child;
			if (current * 2 + 2 == heapSize)
			{
				child = current * 2 + 1;
			}
			else
			{
				child = compare(current * 2 + 1, current * 2 + 2) ? current * 2 + 1 : current * 2 + 2;
			}

			if (compare(current, child))
			{
				break;
			}

			State temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;

			current = child;
		}
	}

	State top() {
		return heap[0];
	}

	bool empty() {
		if (heapSize <= 0)
			return true;
		return false;
	}

};

int solve() {
	State start(x1, y1, 0, NOTHING);
	//PriorityQueue pq;
	priority_queue<State, vector<State>, compareState> pq;
	pq.push(start);

	while (!pq.empty()) {
		State curr = pq.top();
		pq.pop();
		if (curr.x == x2 && curr.y == y2)
			return curr.moveCnt;
		if (curr.currDirec == NOTHING) {
			for (int d = 0; d < 4; d++) {
				State next(curr.x + moveX[d], curr.y + moveY[d], curr.moveCnt + 1, d);
				pq.push(next);
			}
		}
		else if (curr.currDirec == UP || curr.currDirec == DOWN) {
			State next1(curr.x + moveX[1], curr.y + moveY[1], curr.moveCnt + 1, 1);
			State next2(curr.x + moveX[3], curr.y + moveY[3], curr.moveCnt + 1, 3);
			pq.push(next1);
			pq.push(next2);
		}
		else if (curr.currDirec == LEFT || curr.currDirec == RIGHT) {
			State next1(curr.x + moveX[0], curr.y + moveY[0], curr.moveCnt + 1, 0);
			State next2(curr.x + moveX[2], curr.y + moveY[2], curr.moveCnt + 1, 2);
			pq.push(next1);
			pq.push(next2);
		}
	}

	return 0;
}

int abs(int a) {
	if (a < 0)
		return -a;
	return a;
}

int solve2() {
	x2 = x1 - x2;
	y2 = y1 - y2;
	x2 = abs(x2);
	y2 = abs(y2);

	if (x2 == y2)
		return x2 * 2;

	if (x2 > y2) {
		int tmp = x2;
		x2 = y2;
		y2 = tmp;
	}

	if ((y2 - x2) % 2 == 0) {
		int val = (y2 - x2) / 2;
		return (x2 * 2) + val + val * 3;
	}
	else {
		int val = (y2 - x2) / 2;
		return (x2 * 2) + (val + 1) + val * 3;
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("#%d %d\n", tc, solve2());
	}
	return 0;
}
