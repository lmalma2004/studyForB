#include <iostream>

using namespace std;

int T;
int N, M;
pair<int, int> home[20];

int getDistance(int y, int x, pair<int, int> home) {
	int result;
	result = abs(y - home.first) + abs(x - home.second);
	return result;
}

int getHome(int k, int count) {
	int distance;
	int max = 0;
	int result;
	int cost;
	int money;

	cost = k * k + (k - 1)*(k - 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			result = 0;
			money = 0;

			for (int n = 0; n < count; n++) {
				distance = getDistance(i, j, home[n]);
				if (distance < k) {
					result++;
				}
			}
			if (result > max) {
				max = result;
			}
		}
	}

	money = M * max;
	if (cost > money)
		return 0;

	return max;
}

int solve(int count) {
	int max = 0;
	int k = 1;
	int result;

	int left;
	int right = N;

	while (true) {

		if (left == right) {
			for (int i = k; i < right+3; i++) {
				result = getHome(i, count);
				if (result > max) {
					max = result;
				}
			}
			break;
		}

		result = getHome(k, count);

		if (result > max) {
			left = k;
			k = (left + right) / 2;
			max = result;
		}
		else {
			right = k;
			k = (left + right) / 2;
		}
	}

	return max;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		int count = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int temp;
				scanf("%d", &temp);
				if (temp == 1) {
					home[count].first = i;
					home[count].second = j;
					count++;
				}
			}
		}

		printf("#%d %d\n", tc, solve(count));
	}
	return 0;
}
