#include <iostream>
#include <queue>
using namespace std;
int movey[4] = { 1, -1, 0, 0 };
int movex[4] = { 0,0, -1, 1 };

class Atom {
public:
	int y, x;
	int k;
	int direc;
	bool exist;

	void move() {
		y += movey[direc];
		x += movex[direc];
	}
	void back() {
		y -= movey[direc];
		x -= movex[direc];
	}
};

int T, N;
Atom atoms[1000];

bool isExist(int index) {
	if (atoms[index].exist == true)
		return true;
	else
		return false;
}

//up 0 down 1 left 2 right 3
bool isMeet(int a, int b) {
	if (atoms[a].direc == atoms[b].direc)
		return false;
	else if (atoms[a].direc == 2 && atoms[b].direc == 3 && atoms[a].y == atoms[b].y &&
		atoms[a].x > atoms[b].x) {
		return true;
	}
	else if (atoms[a].direc == 3 && atoms[b].direc == 2 && atoms[a].y == atoms[b].y &&
		atoms[b].x > atoms[a].x) {
		return true;
	}
	else if (atoms[a].direc == 1 && atoms[b].direc == 0 && atoms[a].x == atoms[b].x &&
		atoms[a].y > atoms[b].y) {
		return true;
	}
	else if (atoms[a].direc == 0 && atoms[b].direc == 1 && atoms[a].x == atoms[b].x &&
		atoms[b].y > atoms[a].y) {
		return true;
	}//
	else if (atoms[a].direc == 2 && atoms[b].direc == 0 &&
		(atoms[a].x - atoms[b].x) == (atoms[a].y - atoms[b].y) && (atoms[a].x - atoms[b].x) > 0 && (atoms[a].y - atoms[b].y) > 0) {
		//if((atoms[a].x - atoms[b].x) > 0 &&  (atoms[a].y - atoms[b].y) > 0)
		return true;
	}
	else if (atoms[a].direc == 2 && atoms[b].direc == 1 &&
		(atoms[a].x - atoms[b].x) == (atoms[b].y - atoms[a].y) && (atoms[a].x - atoms[b].x) > 0 && (atoms[b].y - atoms[a].y) > 0) {
		//if ((atoms[a].x - atoms[b].x) > 0 && (atoms[b].y - atoms[a].y) > 0)
		return true;
	}//
	else if (atoms[a].direc == 3 && atoms[b].direc == 0 &&
		(atoms[b].x - atoms[a].x) == (atoms[a].y - atoms[b].y) && (atoms[b].x - atoms[a].x) > 0 && (atoms[a].y - atoms[b].y) > 0) {
		//if ((atoms[b].x - atoms[a].x) > 0 && (atoms[a].y - atoms[b].y) > 0)
		return true;
	}
	else if (atoms[a].direc == 3 && atoms[b].direc == 1 &&
		(atoms[b].x - atoms[a].x) == (atoms[b].y - atoms[a].y) && (atoms[b].x - atoms[a].x) > 0 && (atoms[b].y - atoms[a].y) > 0) {
		//if ((atoms[b].x - atoms[a].x) > 0 && (atoms[b].y - atoms[a].y) > 0)
		return true;
	}//
	else if (atoms[a].direc == 0 && atoms[b].direc == 2 &&
		(atoms[b].x - atoms[a].x) == (atoms[b].y - atoms[a].y) && (atoms[b].x - atoms[a].x) > 0 && (atoms[b].y - atoms[a].y) > 0) {
		//if ((atoms[b].x - atoms[a].x) > 0 && (atoms[b].y - atoms[a].y) > 0)
		return true;
	}
	else if (atoms[a].direc == 1 && atoms[b].direc == 2 &&
		(atoms[b].x - atoms[a].x) == (atoms[a].y - atoms[b].y) && (atoms[b].x - atoms[a].x) > 0 && (atoms[a].y - atoms[b].y) > 0) {
		//if ((atoms[b].x - atoms[a].x) > 0 && (atoms[a].y - atoms[b].y) > 0)
		return true;
	}
	else if (atoms[a].direc == 0 && atoms[b].direc == 3 &&
		(atoms[a].x - atoms[b].x) == (atoms[b].y - atoms[a].y) && (atoms[a].x - atoms[b].x) > 0 && (atoms[b].y - atoms[a].y) > 0) {
		//if ((atoms[a].x - atoms[b].x) > 0 && (atoms[b].y - atoms[a].y) > 0)
		return true;
	}
	else if (atoms[a].direc == 1 && atoms[b].direc == 3 &&
		(atoms[a].x - atoms[b].x) == (atoms[a].y - atoms[b].y) && (atoms[a].x - atoms[b].x) > 0 && (atoms[a].y - atoms[b].y) > 0) {
		//if ((atoms[a].x - atoms[b].x) > 0 && (atoms[a].y - atoms[b].y) > 0)
		return true;
	}
	else
		return false;
}

int calDistance(int a, int b) {
	return abs(atoms[a].x - atoms[b].x) + abs(atoms[a].y - atoms[b].y);
}

class couple {
public:
	int pairs[4];
	int n;
	int distance;
};

class comparatorAtoms {
public:
	bool operator()(const couple& c1, const couple& c2) {
		if (c1.distance != c2.distance)
			return c1.distance > c2.distance;
		else
			return c1.n < c2.n;
	}
};

int calEnerge(couple c) {
	int result = 0;
	for (int i = 0; i < c.n; i++) {
		if (isExist(c.pairs[i])) {
			atoms[c.pairs[i]].exist = false;
			result += atoms[c.pairs[i]].k;
		}
	}
	return result;
}

couple Merge(const couple& a, const couple& b) {
	couple temp = a;
	temp.pairs[temp.n] = b.pairs[1];
	temp.n++;
	return temp;
}

int solve2() {
	priority_queue<couple, vector<couple>, comparatorAtoms> pq;
	priority_queue<couple, vector<couple>, comparatorAtoms> pq2;
	int result = 0;

	for (int i = 0; i < N - 1; i++) {
		for (int j = 1; j < N; j++) {
			if (isMeet(i, j)) {
				couple temp;
				temp.pairs[0] = i;
				temp.pairs[1] = j;
				temp.n = 2;
				temp.distance = calDistance(i, j);
				pq.push(temp);
			}
		}
		if (!pq.empty()) {
			couple merged;
			merged = pq.top();
			pq.pop();

			if (pq.empty()) {
				pq2.push(merged);
			}
			else {
				while (!pq.empty()) {
					couple temp = pq.top();
					pq.pop();
					if (merged.distance == temp.distance) {
						merged = Merge(merged, temp);
						if (pq.empty())
							pq2.push(merged);
					}
					else {
						pq2.push(merged);
						pq2.push(temp);
					}
				}
			}
		}

	}

	while (!pq2.empty()) {
		couple temp;
		temp = pq2.top();
		pq2.pop();
		int live = 0;

		for (int i = 0; i < temp.n; i++) {
			//cout << temp.pairs[i] << " : " << atoms[temp.pairs[i]].exist << endl;
			//cout << temp.distance << endl;
			if (isExist(temp.pairs[i])) {
				live++;
			}
		}
		//cout << endl;
		if (live > 1) {
			result += calEnerge(temp);
		}

	}

	return result;
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &atoms[i].x, &atoms[i].y, &atoms[i].direc, &atoms[i].k);
			atoms[i].exist = true;
		}

		printf("#%d %d\n", tc, solve2());
	}
	return 0;
}


