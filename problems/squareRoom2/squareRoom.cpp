#include <iostream>
#define MAX     1000
#define LEFT    0
#define RIGHT   1
#define UP      2
#define DOWN    3
 
using namespace std;
 
int map[MAX][MAX];
int mapOfNum[MAX][MAX];
#include <iostream>
#define MAX     1000
#define LEFT    0
#define RIGHT   1
#define UP      2
#define DOWN    3
 
using namespace std;
 
int map[MAX][MAX];
int mapOfNum[MAX][MAX];
int memo[MAX + 1][MAX + 1][4];
int T;
int N;
 
void init() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mapOfNum[i][j] = 0;
            for (int d = 0; d < 4; d++)
                memo[i][j][d] = -1;
        }
    }
}
 
bool isRange(int row, int col) {
    if (row < 0 || col < 0)
        return false;
    if (row >= N || col >= N)
        return false;
    return true;
}
 
int getHowManyMove(int row, int col, int direc) {
    //if (!isRange(row, col))
    //  return 0;
    if (memo[row][col][direc] != -1)
        return memo[row][col][direc];
    int count = 0;
 
    if (direc == UP) {
        if (isRange(row - 1, col) && (map[row - 1][col] - map[row][col]) == 1) {
            count++;
            for (int d = 0; d < 4; d++)
                count += getHowManyMove(row - 1, col, d);
        }
    }
    else if (direc == DOWN) {
        if (isRange(row + 1, col) && (map[row + 1][col] - map[row][col]) == 1) {
            count++;
            for (int d = 0; d < 4; d++)
                count += getHowManyMove(row + 1, col, d);
        }
    }
    else if (direc == LEFT) {
        if (isRange(row, col - 1) && (map[row][col - 1] - map[row][col]) == 1) {
            count++;
            for (int d = 0; d < 4; d++)
                count += getHowManyMove(row, col - 1, d);
        }
    }
    else if (direc == RIGHT) {
        if (isRange(row, col + 1) && (map[row][col + 1] - map[row][col]) == 1) {
            count++;
            for (int d = 0; d < 4; d++)
                count += getHowManyMove(row, col + 1, d);
        }
    }
 
    memo[row][col][direc] = count;
    return count;
}
 
void solve() {
    int max = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int currMax = 0;
            for (int d = 0; d < 4; d++) {
                int moveNum = getHowManyMove(i, j, d);
                if (currMax < moveNum)
                    currMax = moveNum;
            }
            if (max < currMax)
                max = currMax;
            mapOfNum[i][j] = currMax;
        }
    }
 
    int minRoomNum = 10000000;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mapOfNum[i][j] == max) {
                if (map[i][j] < minRoomNum)
                    minRoomNum = map[i][j];
            }
        }
    }
    cout << minRoomNum << " " << max + 1 << endl;
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        init();
        for(int i=0; i<N; i++)
            for (int j = 0; j < N; j++) {
                int roomNum;
                scanf("%d", &roomNum);
                map[i][j] = roomNum;
            }
        printf("#%d ", tc);
        solve();
    }
    return 0;
}
