#include <iostream>
#define MAX 100
 
using namespace std;
 
int T;
int N;
int problems[MAX]; //문제들
int allScore = 0; //문제 다맞았을때의 score
 
bool hasScore[10000]; //시험점수 체크
int scores[10000]; //시험점수들
int scoresSize = 0; //시험점수들 개수
 
#include <iostream>
#define MAX 100
 
using namespace std;
 
int T;
int N;
int problems[MAX]; //문제들
int allScore = 0; //문제 다맞았을때의 score
 
bool hasScore[10000]; //시험점수 체크
int scores[10000]; //시험점수들
int scoresSize = 0; //시험점수들 개수
 
void init() {
    for (int i = 0; i <= allScore; i++)
        hasScore[i] = false;
    allScore = 0;
    scores[0] = 0;
    scoresSize = 1; //0점도 가능한 시험점수라 1부터 시작
}
 
int solve() {
    //현재 가지고 있는 시험 점수리스트들에 대하여
    //문제들을 1개씩 풀어보며 나오는 점수들을 카운팅한다.
    for (int i = 0; i < N; i++) {
        int currSize = scoresSize; //현재 가능한 점수들의 개수
        for (int j = 0; j < currSize; j++) {
            //가능한 점수리스트에 없다면 추가해준다.
            if (hasScore[scores[j] + problems[i]] == false) {
                scores[scoresSize] = scores[j] + problems[i];
                scoresSize++;
                hasScore[scores[j] + problems[i]] = true;
            }
        }
    }
    return scoresSize;
}
 
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);
        init();
        for (int i = 0; i < N; i++) {
            int score;
            scanf("%d", &score);
            problems[i] = score;
            allScore += score;
        }
        printf("#%d %d\n", tc, solve());
    }
    return 0;
}
