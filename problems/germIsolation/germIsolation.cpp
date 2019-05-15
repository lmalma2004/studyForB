#include <iostream>

using namespace std;

int movey[4] = { -1, 1, 0, 0 };
int movex[4] = { 0, 0, -1, 1 };

class Germ {
public:
	int x;
	int y;
	int n;
	int direc;
	int root;
	bool live;
	void move() {
		x += movex[direc];
		y += movey[direc];
	}
	Germ() {
		live = false;
	}
};

int T;
int N, M, K;

class DisjointSet {
public:
	Germ germs[1000];

	int find(int u) {
		if (u == germs[u].root)
			return u;
		return u = find(germs[u].root);
	}

	void merge(int u, int v) {
		u = find(u);
		v = find(v);
		if (u == v)
			return;
		germs[v].root = u;
		germs[v].live = false;
	}
	bool isMerge(const int& u, const int& v) {
		if (germs[u].x == germs[v].x && germs[u].y == germs[v].y && germs[u].live == true && germs[v].live == true) {
			return true;
		}
		return false;
	}
};

DisjointSet d;

bool isMedicine(const Germ& g) {
	if (g.x == 0 || g.y == 0 || g.x == N - 1 || g.y == N - 1) {
		return true;
	}
	return false;
}

int solve() {
	int direc;
	int count = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < K; j++) {
			if (d.germs[j].live == true) {
				d.germs[j].move();
				if (isMedicine(d.germs[j])) {
					d.germs[j].n /= 2;
					if (d.germs[j].n == 0)
						d.germs[j].live = false;
					if (d.germs[j].direc == 0) {
						d.germs[j].direc = 1;
					}
					else if (d.germs[j].direc == 1) {
						d.germs[j].direc = 0;
					}
					else if (d.germs[j].direc == 2) {
						d.germs[j].direc = 3;
					}
					else if (d.germs[j].direc == 3) {
						d.germs[j].direc = 2;
					}
				}
			}
		}

		for (int j = 0; j < K - 1; j++) {
			int max = d.germs[j].n;
			int sum = d.germs[j].n;
			if (d.germs[j].live == true) {
				for (int k = j + 1; k < K; k++) {
					if (d.isMerge(j, k)) {
						d.merge(j, k);
						sum += d.germs[k].n;
						if (max < d.germs[k].n) {
							max = d.germs[k].n;
							d.germs[j].direc = d.germs[k].direc;
						}
					}
				}
				count++;
			}
			d.germs[j].n = sum;
		}
		if (count < 2)
			break;
	}
	
	int result = 0;

	for (int i = 0; i < K; i++) {
		if (d.germs[i].live == true) {
			result += d.germs[i].n;
		}
	}

	return result;
	
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &d.germs[i].y, &d.germs[i].x, &d.germs[i].n, &d.germs[i].direc);
			d.germs[i].direc--;
			d.germs[i].live = true;
			d.germs[i].root = i;
		}

		printf("#%d %d\n", tc, solve());
	}
	return 0;
}

