#include <iostream>
using namespace std;
 
int T;
int N, M;
 
class BurgerManager {
public:
    int pairs[400]; //어울리지 않는 쌍들
    int pairsSize;  //어울리지 않는 쌍들의 size
    int pairsCheck[21][21]; //쌍들 추가해줄때마다 체크
public:
    BurgerManager() {
        init();
    }
    void init() {
        for (int i = 0; i < N + 1; i++)
            for (int j = 0; j < N + 1; j++)
                pairsCheck[i][j] = false;
        pairsSize = 0;
    }
    bool isChecked(int a, int b) {
        return pairsCheck[a][b];
    }
    //어울리지 않는 쌍 a, b 를 추가
    void push(int a, int b) {
        //이미 있는 쌍이라면 리턴
        if (isChecked(a, b))
            return;
        int newPair = ((1 << a) | (1 << b));
        pairs[pairsSize] = newPair;
        checkPair(a, b);
        pairsSize++;
    }
    void checkPair(int a, int b) {
        pairsCheck[a][b] = true;
        pairsCheck[b][a] = true;
    }
    //used로 버거를 만들수 있는지 검사
    bool isPossible(int used) {
        for (int i = 0; i < pairsSize; i++) {
            if ((pairs[i] & used) == pairs[i])
                return false;
        }
        return true;
    }
    //현재 재료used에서 시작해서 ingredient부터 N까지의 재료를 사용해서 만들 수 있는 
    //모든 버거의 경우의 수를 리턴한다.
    int getBurger(int used, int ingredient) {
        // used로 만들 수 없다면 어떤재료를 추가하든 만들 수 없으니 0을 리턴
        if (!isPossible(used))
            return 0;
 
        // used로 만들 수 있는 경우 -> 1개
        int ret = 1; 
         
        //f(현재재료, 재료시작) = f(현재재료 + ingredient, ingredient의 다음재료) +
        //                       f(현재재료 + ingredient의 다음재료, ingredient의 다음재료의 다음재료) + 
        //                        ...
        for (int i = ingredient; i < N + 1; i++)
            ret += getBurger(used | (1 << i), i + 1);
 
        return ret;
    }
    int getAllBurger() {
        //어울리지 않는 쌍이 없다면 경우의 수는 2의 N제곱
        if (pairsSize == 0)
            return (1 << N);
        //아무것도 없는 재료에서 1재료부터 N까지를 사용하여 만들 수 있는 버거의 수를 리턴
        return getBurger(0, 1); 
    }
};
 
BurgerManager BM;
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d %d", &N, &M);
        BM.init();
        for (int i = 0; i < M; i++) {
            int ingredient1;
            int ingredient2;
            scanf("%d %d", &ingredient1, &ingredient2);
            BM.push(ingredient1, ingredient2);
        }
        printf("#%d %d\n", tc, BM.getAllBurger());
    }
    return 0;
}
