#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


int T;
int N, K;
int A[100000];


int makeEqualityArray(int arr[], int n, int c) {
    int nTries = 0;

    // 왼->오 깎기
    for (int i = 1; i < n; i++) {
        int gap = arr[i] - arr[i - 1];

        if (gap > c) {
            int decrement = gap - c;
            arr[i] -= decrement;
            nTries += decrement;
        }
    }

    // 오->왼 깎기
    for (int i = n - 2; i >= 0; i--) {
        int gap = arr[i] - arr[i + 1];

        if (gap > c) {
            int decrement = gap - c;
            arr[i] -= decrement;
            nTries += decrement;
        }
    }

    return nTries;
}

// k번이하로 수정해서 수열에서 인접한 숫자의 차이가 모두 c 이하라면, true 반환
bool isPossible(int arr[], int n, int k, int c) {
    static int copiedArray[100000];

    memcpy(copiedArray, arr, sizeof(copiedArray));
    int totalCost = makeEqualityArray(copiedArray, n, c);

    return (totalCost <= k);
}

int minInArray(int arr[], int n) {
    int minValue = arr[0];
    for (int i = 0; i < n; i++) {
        minValue = min(minValue, arr[i]);
    }
    return minValue;
}

int maxInArray(int arr[], int n) {
    int maxValue = arr[0];
    for (int i = 0; i < n; i++) {
        maxValue = max(maxValue, arr[i]);
    }
    return maxValue;
}

int solve() {
    int lowerBound = 0;
    int upperBound = maxInArray(A, N) - minInArray(A, N);

    while (lowerBound < upperBound) {
        int mid = (lowerBound + upperBound) / 2;

        if (isPossible(A, N, K, mid)) {
            upperBound = mid;
        }
        else {
            lowerBound = mid + 1;
        }
    }

    return lowerBound;
}


int main() {
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        scanf("%d %d", &N, &K);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }

        int answer = solve();
        printf("#%d %d\n", tc, answer);
    }

    return 0;
}
