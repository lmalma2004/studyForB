#include <iostream>

using namespace std;

int T;
int N;
double x[10];
double m[10];

double getForce(int i, double current) {
	double f;
	f = m[i] / ((x[i] - current)*(x[i] - current));
	return f;
}

double Abs(double p) {
	if (p < 0)
		return -p;
	else
		return p;
}

double getBalance(int n, double prePoint, double curPoint, double left, double right) {
	double leftF = 0;
	double rightF = 0;

	if (Abs(curPoint - prePoint) <= 0.000000000001)
		return curPoint;

	prePoint = curPoint;

	for (int i = 0; i <= n; i++) {
		leftF += getForce(i, curPoint);
	}
	for (int i = n + 1; i < N; i++) {
		rightF += getForce(i, curPoint);
	}

	if (leftF > rightF) {
		double next = (curPoint + right) / 2;
		return getBalance(n, curPoint, next, curPoint, right);
	}
	else if (leftF == rightF) {
		return curPoint;
	}
	else {
		double next = (left + curPoint) / 2;
		return getBalance(n, curPoint, next, left, curPoint);
	}

}

//a번째 균형점을 찾아 x좌표 반환
double solve(int a) {
	double result = (x[a] + x[a + 1]) / 2;
	double left = x[a];
	double right = x[a + 1];
	  
	result = getBalance(a, 0, result, left, right);

	return result;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf", &x[i]);
		for (int i = 0; i < N; i++)
			scanf("%lf", &m[i]);

		printf("#%d ", tc);

		for (int i = 0; i < N - 1; i++) {
			printf("%.10lf ", solve(i));
		}
		cout << endl;
		
	}
	return 0;
}
