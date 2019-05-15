#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

bool dead = false;
bool live = true;

int movey[4] = { -1,1,0,0 }; //down, up, right, left
int movex[4] = { 0,0,1,-1 };

class cell {
public:
	int x;
	int y;
	int initX;
	int currX;
	bool state;

	cell() {
		initX = 0;
		state = dead;
	}

	void updatestate() {
		if (currX <= -(initX))
			state = dead;
		else
			state = live;
	}
	void initstate() {
		x = 0;
		y = 0;
		initX = 0;
		currX = 0;
		state = dead;
	}
};

class cellcomparator {
public:
	bool operator()(const cell& c0, const cell& c1) {
		return c0.initX < c1.initX;
	}
};

int T, K, N, M;
cell cellgraph[850][850];
const int startx = 350;
const int starty = 350;
int callivecell() {
	int count = 0;
	for (int i = 0; i < 800; i++)
		for (int j = 0; j < 800; j++) {
			if (cellgraph[i][j].state == live) {
				count++;
			}
		}
	return count;
}

void printcell() {
	for (int i = 335; i < 375; i++) {
		for (int j = 335; j < 375; j++) {
			//if (cellgraph[i][j].state == live)
			//	cout << "*";
			//else
			printf("%d", cellgraph[i][j].currX);
		}
		printf("\n");
	}
}

void onego(queue<cell>& livecell) {
	cell temp;
	int n = livecell.size();
	for(int i=0; i<n; i++){
		temp = livecell.front();
		livecell.pop();
		cellgraph[temp.y][temp.x].currX--;
		cellgraph[temp.y][temp.x].updatestate();
		if (cellgraph[temp.y][temp.x].state == live)
			livecell.push(temp);
	}
}

void pushActivecell(queue<cell>& livecell, priority_queue<cell, vector<cell>, cellcomparator>& pq) {
	cell temp;
	for (int i = 0; i < livecell.size(); i++) {
		temp = livecell.front();
		livecell.pop();
		if (cellgraph[temp.y][temp.x].currX <= 0)
			pq.push(temp);
		livecell.push(temp);
	}
}

void breed(queue<cell>& livecell, const cell& current) {
	cell temp;
	for (int i = 0; i < 4; i++) {
		temp.x = current.x + movex[i];
		temp.y = current.y + movey[i];
		//번식안한 위치면
		if (cellgraph[temp.y][temp.x].initX == 0) {
			temp.initX = current.initX;
			temp.currX = current.initX;
			temp.updatestate();
			cellgraph[temp.y][temp.x] = temp;
			livecell.push(temp);
		}

	}
}
int solve() {
	int result;

	priority_queue<cell, vector<cell>, cellcomparator> pq;
	queue<cell> livecell;
	//초기화
	for (int i = 0; i < 800; i++)
		for (int j = 0; j < 800; j++) {
			//살아있고 활성화상태면 큐에 넣는다.
			if (cellgraph[i][j].state == live && cellgraph[i][j].currX <= 0) {
				pq.push(cellgraph[i][j]);
			}
			if (cellgraph[i][j].state == live)
				livecell.push(cellgraph[i][j]);
		}

	for (int time = 0; time < K; time++) {
		pushActivecell(livecell, pq);
		//1시간흐른다.
		onego(livecell);
		//pq에는 이미 살아있고 활성화된 것만 들어가있음
		while (!pq.empty()) {
			cell current = pq.top();
			pq.pop();
			//번식할 장소를 살피고 번식한다.
			breed(livecell, current);
		}
	}

	//result = callivecell();
	result = livecell.size();
	return result;

}
int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		int cellnumber;

		scanf("%d %d %d", &N, &M, &K);
		for (int i = starty; i < starty + N; i++)
			for (int j = startx; j < startx + M; j++) {
				scanf("%d", &cellgraph[i][j].initX);
				cellgraph[i][j].x = j;
				cellgraph[i][j].y = i;
				cellgraph[i][j].currX = cellgraph[i][j].initX;
				cellgraph[i][j].updatestate();
			}

		cellnumber = solve();

		printf("#%d %d\n", tc, cellnumber);

		for (int i = 0; i < 800; i++)
			for (int j = 0; j < 800; j++) {
				cellgraph[i][j].initstate();
			}
	}

	return 0;
}

