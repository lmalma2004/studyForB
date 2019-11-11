#include <iostream>
#define MAX 100
#define MILLION 1000000000
using namespace std;
int T;
int N;
long long memo[1024][10][MAX]; //1024 = (1<<10)
int BN[MAX]; //삐끗수
 
void init() {
    for (int i = 0; i < 1024; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < MAX; k++)
                memo[i][j][k] = -1;
    for (int i = 0; i < MAX; i++)
        BN[i] = -10;
}
int abs(int n) {
    if (n > 0)
        return n;
    return -n;
}
//BN[idx]에 n을 놓을 수 있는지 검사
bool isPlaced(int n, int idx) {
    if (idx == 0 && n == 0)
        return false;
    if (idx == 0)
        return true;
    if (abs(BN[idx - 1] - n) == 1)
        return true;
    return false;
}
//used   : 현재 사용한 숫자들
//preNum : 현재 숫자를 넣어봐야 할 자리 바로 전의 숫자 (BN[len - 1] 의 숫자)
//len    : 현재 숫자를 넣어봐야 할 자리 (BN[len] 에 넣어보는 것)
//-> 현재 사용한 숫자들이 used 이고
//-> 현재 넣어봐야 할 자리가 len 이며
//-> 현재 숫자를 넣어봐야 할 자리 바로 전의 숫자가 preNum일때 
//-> 만들수 있는 삐끗수의 경우의 수를 반환한다.
long long getBN(int used, int preNum, int len) {
    //len 이 N인 경우는 BN[0] ~ BN[N-1] 까지 다 숫자를 만들었지만 삐끗수가 아닌경우임
    //따라서 0 리턴
    if (len == N)
        return 0;
    if (memo[used][preNum][len] != -1)
        return memo[used][preNum][len];
 
    long long count = 0LL;
    for (int i = 0; i < 10; i++) {
        if (isPlaced(i, len)) {
            //삐끗수를 만든경우
            if (len == N - 1 && (used | (1 << i)) == (1023)) {
                count++;
                count %= MILLION;
                continue;
            }
            BN[len] = i;
            count += getBN(used | (1<<i), i, len + 1);
            count %= MILLION;
        }
    }
 
    memo[used][preNum][len] = count;
    return count;
}
 
long long solve() {
    long long count = 0;
 
    //BN[0]이 i로 시작해서 만들 수 있는 삐끗수들을 모두 더해준다.
    for (int i = 0; i < 10; i++) {
        if (isPlaced(i, 0)) {
            BN[0] = i;
            count += getBN((1<<i), i, 1);
            count %= MILLION;
        }
    }
    return count;
}
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        init();
        scanf("%d", &N);
        printf("#%d %lld\n", tc, solve());
    }
    return 0;
}
