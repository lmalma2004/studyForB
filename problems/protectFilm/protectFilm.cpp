#include <iostream>
#include <queue>

using namespace std;

int T, D, W, K;

class Level {
public:
	bool cells[20];
	Level() {
	}

};

class Film {
public:
	int injectioned;
	int visited = 0;
	Level levels[13];

	Film() {
		injectioned = 0;
	}
};

Film film;
Film makeAdj(const Film& curr, const int& level, const bool& state) {
	Film temp;
	temp = curr;
	temp.visited = level;
	temp.injectioned = ((1 << level) | temp.injectioned);
	for (int i = 0; i < W; i++)
		temp.levels[level].cells[i] = state;

	return temp;
}

bool isPossible(const Film& curr, const int& index) {
	bool flag;

	for (int i = 0; i < D - (K - 1); i++) {
		flag = true;
		for (int j = i; (j < i + (K - 1)) && j < 12; j++) {
			if (curr.levels[j].cells[index] != curr.levels[j + 1].cells[index]) {
				flag = false;
			}
		}
		if (flag)
			return true;
	}
	return false;
}

bool isPass(const Film& curr) {
	for (int i = 0; i < W; i++) {
		if (!isPossible(curr, i))
			return false;
	}
	return true;
}

int calCount(const int& injectioned) {
	int count = 0;
	for (int i = 0; i < D; i++) {
		if (((1 << i) & injectioned) != 0)
			count++;
	}
	return count;
}

int solve() {
	queue<Film> q;
	queue<Film> q2;
	q.push(film);
	q2.push(film);

	while (!q.empty()) {
		while(!q2.empty()){
			Film curr = q2.front();
			q2.pop();
			if (isPass(curr)) {
				return calCount(curr.injectioned);
			}
		}
		Film curr = q.front();
		q.pop();
		for (int i = curr.visited; i < D; i++) {
			if (((1 << i) & curr.injectioned) == 0) {
				Film temp;
				temp = makeAdj(curr, i, false);
				q.push(temp);
				q2.push(temp);
				temp = makeAdj(curr, i, true);
				q.push(temp);
				q2.push(temp);
			}
		}

	}

	return -1;
}

int main() {
	int tmp;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d", &D, &W, &K);

		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &tmp);
				if (tmp == 0)
					film.levels[i].cells[j] = false;
				else if (tmp == 1)
					film.levels[i].cells[j] = true;
			}
		}

		printf("#%d %d\n", tc, solve());
	}

	return 0;
}
