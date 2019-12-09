#include <iostream>
#include <algorithm>
#define MAX 1000000
using namespace std;

int T;
int N;

class Report {
public:
	int t;
	int d;
};

Report reports[MAX];
int msize = 0;

bool compare(int left, int right) {
	if (reports[left].d >= reports[right].d)
		return true;
	return false;
}
bool compareReport(const Report& a, const Report& b) {
	if (a.d > b.d)
		return true;
	return false;
}


void swap(Report input[], int a, int b) {
	Report temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}

void quickSort(Report input[], int left, int right) {
	if (left < right) {
		int pivot = left;
		int currLeft = left;
		int currRight = right;
		while (currLeft < currRight) {
			while (input[currLeft].d >= input[pivot].d && currLeft < right) {
				currLeft++;
			}
			while (input[currRight].d < input[pivot].d) {
				currRight--;
			}
			if (currLeft < currRight) {
				swap(input, currLeft, currRight);
			}
		}
		swap(input, pivot, currRight);
		quickSort(input, left, currRight - 1);
		quickSort(input, currRight + 1, right);
	}
}

void qsort(int left, int right) {
	int pivot;
	int i;
	int j;
	Report tmp;

	if (left < right) {
		pivot = left;
		i = left;
		j = right;
		while (i < j) {
			while (compare(i, pivot) && i < right)
				i++;
			while (!compare(j, pivot))
				j--;
			if (i < j) {
				tmp = reports[i];
				reports[i] = reports[j];
				reports[j] = tmp;
			}
		}
		tmp = reports[pivot];
		reports[pivot] = reports[j];
		reports[j] = tmp;
		
		qsort(left, j - 1);
		qsort(j + 1, right);
	}
}

int cal(int index, int X) {
	if (reports[index].d < X)
		X = reports[index].d;
	X = X - reports[index].t;
	return X;
}

int solve() {
	//quickSort(reports, 0, N - 1);
	//qsort(0, N - 1);
	sort(reports, reports + N, compareReport);
	int X = reports[0].d;

	for (int i = 0; i < N; i++) {
		//cout << reports[i].d << endl;
		X = cal(i, X);
	}
	return X;
}

void init() {
	msize = 0;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		init();
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &reports[msize].t, &reports[msize].d);
			msize++;
		}

		printf("#%d %d\n", tc, solve());
	}
	return 0;
}
