#include <iostream>
#include <queue>

using namespace std;

class BatteryCharge {
public:
	int x;
	int y;
	int C;
	int P;
	int index;
};

class Comparator {
public:
	bool operator()(const BatteryCharge& B1, BatteryCharge& B2) {
		return B1.P < B2.P;
	}
};

class Person {
public:
	int x;
	int y;
	int P;
	int index;

	Person() {
		index = -1;
		P = 0;
	}
};

int T;
int M;
int A;

int direcA[100];
int direcB[100];

int movey[5] = { 0, -1, 0, 1, 0 };
int movex[5] = { 0, 0, 1, 0, -1 };

BatteryCharge BC[8];

bool isCharge(const Person& p, const BatteryCharge& b) {
	int distance;
	distance = abs(p.x - b.x) + abs(p.y - b.y);

	if (b.C >= distance)
		return true;
	return false;
}

int chooseBC(Person& p1, int index) {
	int count = 0;
	priority_queue<BatteryCharge, vector<BatteryCharge>, Comparator> q;
	BatteryCharge temp;

	for (int i = 0; i < A; i++) {
		if (isCharge(p1, BC[i])) {
			q.push(BC[i]);
			count++;
		}
	}

	if (q.empty()) {
		p1.P = 0;
		p1.index = -1;
		return count;
	}

	while (index > 0 && !q.empty()) {
		index--;
		temp = q.top();
		q.pop();
	}

	p1.index = temp.index;
	p1.P = temp.P;

	return count;
}

void move(Person& p, int m, int n) {
	if (n == 1) {
		p.x += movex[direcA[m]];
		p.y += movey[direcA[m]];
		p.index = -1;
	}
	else if (n == 2) {
		p.x += movex[direcB[m]];
		p.y += movey[direcB[m]];
		p.index = -1;
	}
}

int solve() {
	int result = 0;
	Person p1;
	Person p2;

	p1.x = 0;
	p1.y = 0;
	p2.x = 9;
	p2.y = 9;

	for (int i = 0; i <= M; i++) {
		int n1 = chooseBC(p1, 1);
		int n2 = chooseBC(p2, 1);
		int c1 = p1.P;
		int c2 = p2.P;
		if (p1.index == p2.index && p1.index != -1) {
			if (n1 == 1 && n2 == 1) {
				p1.P = 0;
			}
			else if (n1 > 1 && n2 > 1) {
				chooseBC(p1, 2);
				chooseBC(p2, 2);

				if (p1.P > p2.P)
					p2.P = c2;
				else
					p1.P = c1;
			}
			else if (n1 == 1 && n2 != 1) {
				chooseBC(p2, 2);
			}
			else if (n2 == 1 && n1 != 1) {
				chooseBC(p1, 2);
			}
		}

		result += p1.P + p2.P;

		if (i != M) {
			move(p1, i, 1);
			move(p2, i, 2);
		}
	}

	return result;
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &M, &A);
		for (int i = 0; i < M; i++)
			scanf("%d", &direcA[i]);
		for (int i = 0; i < M; i++)
			scanf("%d", &direcB[i]);
		for (int i = 0; i < A; i++) {
			scanf("%d %d %d %d", &BC[i].x, &BC[i].y, &BC[i].C, &BC[i].P);
			BC[i].index = i;
			BC[i].x--;
			BC[i].y--;
		}

		printf("#%d %d\n", tc, solve());
	}

	return 0;
}
