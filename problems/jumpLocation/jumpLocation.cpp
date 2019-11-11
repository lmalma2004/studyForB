// 인접한 두 점프대의 높이차 중에서 가장 큰 값을 최소화하도록 점프대를 재배치하려고 한다.
// 인접한 두 점프대의 높이차 : h
// h로 점프대를 배치해본다.(원형)
// N : 5 ~ 10,000
// 점프대 높이 : 1 ~ 100,000
// h 의 MAX : 99,999
// h 의 MIN : 0
 
// 설명할 개념들
// 우선순위 큐 구조
// 탐욕적 접근의 정당성
// binary search (일치하는 값)
// Parametric Search (가장 일치하는 값)
#include <iostream>
#define MAX 10000
 
using namespace std;
 
class PriorityQueue {
public:
    int heap[MAX];
    int heapSize;
public:
    PriorityQueue() {
        heapSize = 0;
    }
    void heapInit(void)
    {
        heapSize = 0;
    }
    bool empty() {
        return heapSize <= 0;
    }
    void push(int value)
    {
        if (heapSize + 1 > MAX)
            return;
 
        heap[heapSize] = value;
 
        int current = heapSize;
        while (current > 0 && heap[current] > heap[(current - 1) / 2])
        {
            int temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
 
        heapSize = heapSize + 1;
    }
    int top() {
        return heap[0];
    }
 
    void pop()
    {
        if (heapSize <= 0)
            return;
        heapSize = heapSize - 1;
        heap[0] = heap[heapSize];
 
        int current = 0;
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = heap[current * 2 + 1] > heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
            }
 
            if (heap[current] > heap[child])
            {
                break;
            }
 
            int temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
 
            current = child;
        }
    }
};
 
int T;
int N;
int top; // 점프대배치의 시작점 (가장높음)
PriorityQueue jump;
 
//h의 높이로 점프대를 배치 해본다. 배치할 수 없다면 false, 배치할 수 있다면 true
//h    : 높이               / j : 점프대들 
//left : 원통의 왼쪽가장자리 / right : 원통의 오른쪽가장자리 
//turn : 현재배치하는 순번(0번째만 다르고 나머지는 같음)
bool placeJumps(int h, PriorityQueue& remainJump, int left, int right, int turn) {
    //점프대들을 다 배치한 경우
    if (remainJump.empty()) {
        if (abs(left - right) > h)
            return false;
        return true;
    }
 
    //제일 처음 배치하는 경우는 top - left, top - right 를 비교해야 함
    if (turn == 0) {
        if (abs(top - left) > h)
            return false;
        if (abs(top - right) > h)
            return false;
        //top - left, top - right 배치가 성공하면 남은 점프대를 배치해보자.
        return placeJumps(h, remainJump, left, right, turn + 1);
    }
 
    int currLeft = remainJump.top();
    remainJump.pop();
    //remainJump가 안남았다면 현재 점프대와 왼쪽가장자리, 오른쪽가장자리를 비교해야함
    if (remainJump.empty()) {
        if (abs(left - currLeft) > h)
            return false;
        if (abs(right - currLeft) > h)
            return false;
    }
 
    int currRight = remainJump.top();
    remainJump.pop();
 
    if (abs(left - currLeft) > h)
        return false;
    if (abs(right - currRight) > h)
        return false;
 
    return placeJumps(h, remainJump, currLeft, currRight, turn + 1);
}
 
int solve() {
    int lo = 0;
    int hi = 99999;
    //반복문 불변식 설명..
    while (lo != hi) {
        PriorityQueue temp = jump;
        int h = (lo + hi) / 2;
        top = temp.top();
        temp.pop();
        int left = temp.top();
        temp.pop();
        int right = temp.top();
        temp.pop();
 
        if (placeJumps(h, temp, left, right, 0))
            hi = h;
        else
            lo = h + 1;
    }
 
    return hi; //hi를 반환하는 이유는?
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        jump.heapInit();
        for (int i = 0; i < N; i++) {
            int j;
            scanf("%d", &j);
            jump.push(j);
        }
        printf("#%d %d\n", tc, solve());
    }
    return 0;
}
