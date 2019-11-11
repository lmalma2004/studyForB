#include <iostream>
#define MAX_ROW 15
#define MAX_COL 12
using namespace std;
 
int T, N, W, H;
int map[MAX_ROW][MAX_COL];
int moveCol[4] = { 0, 0, -1, 1 };
int moveRow[4] = { -1,1,0,0 };
 
void cloneArr(int copy[MAX_ROW][MAX_COL], int orig[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            copy[i][j] = orig[i][j];
}
bool isRange(int r, int c) {
    if (r < 0 || c < 0)
        return false;
    if (r >= H || c >= W)
        return false;
    return true;
}
void pushMapAboutCol(int map[MAX_ROW][MAX_COL], int col) {
    for (int i = H - 1; i >= 0; i--) {
        if (map[i][col] == 0) {
            int row = -1;
            for (int j = i - 1; j >= 0; j--) {
                if (map[j][col] != 0) {
                    row = j;
                    break;
                }
            }
            if (row == -1)
                return;
            map[i][col] = map[row][col];
            map[row][col] = 0;
        }
    }
}
void pushMap(int map[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < W; i++)
        pushMapAboutCol(map, i);
}
void printMap(int map[MAX_ROW][MAX_COL]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << map[i][j] << " ";
        cout << endl;
    }
}
void crashStone(int map[MAX_ROW][MAX_COL], int row, int col) {
    if (!isRange(row, col))
        return;
    if (map[row][col] == 0)
        return;
 
    int rangeOfBreak = map[row][col] - 1;
    map[row][col] = 0;
 
    for (int i = 1; i <= rangeOfBreak; i++) {
        for (int d = 0; d < 4; d++) {
            int nextRow = row + moveRow[d] * i;
            int nextCol = col + moveCol[d] * i;
            crashStone(map, nextRow, nextCol);
        }
    }
}
void crashMap(int map[MAX_ROW][MAX_COL], int col) {
    int row = -1;
    for(int i=0; i<H; i++)
        if (map[i][col] != 0) {
            row = i;
            break;
        }
    if (row == -1)
        return;
    crashStone(map, row, col);
    pushMap(map);
}
int countStone(int map[MAX_ROW][MAX_COL]) {
    int stone = 0;
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if (map[i][j] != 0)
                stone++;
    return stone;
}
int getMinRemainStone(int map[MAX_ROW][MAX_COL], int col, int marble) {
    crashMap(map, col);
 
    if (marble == N)
        return countStone(map);
 
    int min = 999999;
    for (int i = 0; i < W; i++) {
        int nextMap[MAX_ROW][MAX_COL];
        cloneArr(nextMap, map);
        //crashMap(nextMap, i);
        int remainStone = getMinRemainStone(nextMap, i, marble + 1);
        if (min > remainStone)
            min = remainStone;
    }
    return min;
}
int solve() {
    int min = 999999;
    for (int i = 0; i < W; i++) {
        int nextMap[MAX_ROW][MAX_COL];
        cloneArr(nextMap, map);
        int remainStone = getMinRemainStone(nextMap, i, 1);
        if (min > remainStone)
            min = remainStone;
    }
    return min;
}
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d %d %d", &N, &W, &H);
        for(int i=0; i<H; i++)
            for (int j = 0; j < W; j++) {
                int stone;
                scanf("%d", &stone);
                map[i][j] = stone;
            }
        printf("#%d %d\n", tc, solve());
    }
    return 0;
}
