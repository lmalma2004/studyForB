#include <iostream>
#include <vector>
#include <queue>
 
#define MAX 10
 
using namespace std;
 
int abs(int a) {
    if (a < 0)
        return -a;
    return a;
}
 
class Place {
public:
    int x;
    int y;
public:
    Place() {
    }
    void setLoc(int r, int c) {
        x = r;
        y = c;
    }
};
 
 
 
int T, N;
int memo[(1 << 10)][10];
Place home;         //집
Place corp;         //회사
Place clients[MAX]; //고객들
 
 
int getPath(Place p1, Place p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}
 
//방문정보와 현재위치가 주어졌을때 
//현재위치에서 방문안한 고객들을 모두 방문 후 집까지 가는 최소 경로를 반환한다.
//이 함수는 회사에서 집까지 가는 최소경로를 반환하는게 아니다.
int getLowestPath(int visited, int curr) {
    if (memo[visited][curr] != -1)
        return memo[visited][curr];
    //모두방문한 경우
    if (visited == ((1 << N) - 1))
        return getPath(clients[curr], home);
 
    int min = 999999;
    for (int i = 0; i < N; i++) {
        if (visited & (1 << i))
            continue;
        //path: curr다음으로 clients[i]를 방문할때의 가장 짧은 경로
        int path = getPath(clients[curr], clients[i]) + getLowestPath(visited | (1 << i), i);
        if (min > path)
            min = path;
    }
    memo[visited][curr] = min;
    return min;
}
 
int solve2() {
    int visited = 0;
    int min = 999999;
    for (int i = 0; i < N; i++) {
        //path: 회사다음으로 clients[i]를 방문할때의 가장 짧은 경로
        int path = getPath(clients[i], corp) + getLowestPath(visited | (1 << i), i);
        if (min > path)
            min = path;
    }
    return min;
}
 
void memoInit() {
    for (int i = 0; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            memo[i][j] = -1;
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        int xOfCorp; int yOfCorp; //회사의 위치
        int xOfHome; int yOfHome; //집의 위치
        scanf("%d %d", &xOfCorp, &yOfCorp);
        scanf("%d %d", &xOfHome, &yOfHome);
        corp.setLoc(xOfCorp, yOfCorp);
        home.setLoc(xOfHome, yOfHome);
 
        for (int i = 0; i < N; i++) {
            int xOfClient;
            int yOfClient;
            scanf("%d %d", &xOfClient, &yOfClient);
            clients[i].setLoc(xOfClient, yOfClient);
        }
        memoInit();
        printf("#%d %d\n", tc, solve2());
    }
    return 0;
}
