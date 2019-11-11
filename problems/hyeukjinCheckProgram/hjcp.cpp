#include <iostream>
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
 
using namespace std;
 
int T;
int R, C;
 
class Program {
public:
    char map[20][20];
    bool state[20][20][16][4];
    int memory;
    int direc;
    int row, col;
public:
    Program() {
        init();
    }
    void init() {
        direc = RIGHT;
        row = 0;
        col = 0;
        memory = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                for (int k = 0; k < 16; k++)
                    for (int d = 0; d < 4; d++)
                        state[i][j][k][d] = false;
    }
    void cloneArr(char copy[20][20], char orig[20][20]) {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                copy[i][j] = orig[i][j];
    }
    void move() {
        if (direc == LEFT)
            moveLeft();
        else if (direc == RIGHT)
            moveRight();
        else if (direc == UP)
            moveUp();
        else if (direc == DOWN)
            moveDown();
    }
    bool progress() {
        if (state[row][col][memory][direc])
            return false;
        state[row][col][memory][direc] = true;
 
        if (map[row][col] == '<') {
            direc = LEFT;
            move();
        }
        else if (map[row][col] == '>') {
            direc = RIGHT;
            move();
        }
        else if (map[row][col] == '^') {
            direc = UP;
            move();
        }
        else if (map[row][col] == 'v') {
            direc = DOWN;
            move();
        }
        else if (map[row][col] == '_') {
            if (memory == 0)
                direc = RIGHT;
            else
                direc = LEFT;
            move();
        }
        else if (map[row][col] == '|') {
            if (memory == 0)
                direc = DOWN;
            else
                direc = UP;
            move();
        }
        else if (map[row][col] == '?') {
            for (int i = 0; i < 4; i++) {
                direc = i;
                int memory_orig = memory;
                int row_orig = row;
                int col_orig = col;
 
                move();
                if (progress())
                    return true;
 
                memory = memory_orig;
                row = row_orig;
                col = col_orig;
            }
            return false;
        }
        else if (map[row][col] == '.') {
            move();
        }
        else if (map[row][col] == '@') {
            return true;
        }
        else if (map[row][col] == '+') {
            if (memory == 15)
                memory = 0;
            else
                memory++;
            move();
        }
        else if (map[row][col] == '-') {
            if (memory == 0)
                memory = 15;
            else
                memory--;
            move();
        }
        else {
            memory = map[row][col] - '0';
            move();
        }
        return progress();
    }
    void moveLeft() {
        if (col == 0)
            col = C - 1;
        else
            col--;
    }
    void moveRight() {
        if (col == C - 1)
            col = 0;
        else
            col++;
    }
    void moveUp() {
        if (row == 0)
            row = R - 1;
        else
            row--;
    }
    void moveDown() {
        if (row == R - 1)
            row = 0;
        else
            row++;
    }
};
 
Program pg;
 
int main() {
    //freopen("sample_input.txt", "r", stdin);
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d %d", &R, &C);
        int cnt = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                char tmp;
                scanf(" %c", &tmp);
                pg.map[i][j] = tmp;
                if (tmp == '@')
                    cnt++;
            }
        if(cnt == 0)
            printf("#%d NO\n", tc);
        else if (pg.progress())
            printf("#%d YES\n", tc);
        else
            printf("#%d NO\n", tc);
        pg.init();
    }
    return 0;
}
