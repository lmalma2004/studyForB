#include <iostream>
#define UNCHECK -1
#define MAX     10
using namespace std;
 
int T;
int N;
int counting;
int rows[MAX] = { -1, };
 
bool isRange(int row, int col) {
    if (row < 0 || col < 0)
        return false;
    if (row >= N || col >= N)
        return false;
    return true;
}
bool isExistQueen(int row, int col) {
    if (rows[row] == col)
        return true;
    return false;
}
bool isPossible(int row, int col) {
    int currRow = row;
    int currCol = col;
    //leftUp
    while (isRange(currRow, currCol)) {
        if (isExistQueen(currRow, currCol))
            return false;
        currRow--;
        currCol--;
    }
    //rightUp
    currRow = row;
    currCol = col;
    while (isRange(currRow, currCol)) {
        if (isExistQueen(currRow, currCol))
            return false;
        currRow--;
        currCol++;
    }
    //Up
    currRow = row;
    currCol = col;
    while (isRange(currRow, currCol)) {
        if (isExistQueen(currRow, currCol))
            return false;
        currRow--;
    }
    return true;
}
 
int solve(int row) {
    if (row == N)
        return 1;
    for (int j = 0; j < N; j++) {
        if (isPossible(row, j)) {
            rows[row] = j;
            counting += solve(row + 1);
            rows[row] = UNCHECK;
        }
    }
    return 0;
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        counting = 0;
        solve(0);
        printf("#%d %d\n", tc, counting);
    }
    return 0;
}
