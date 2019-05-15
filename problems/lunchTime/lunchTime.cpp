#include <iostream>
#define upFloor 0 //계단 도착 전 위층
#define arrivalStair 1 //계단에 도착
#define waiting 2 //기다림
#define moving 3 //내려가는중
#define arrival 4 //도착

using namespace std;

int T, N, K;
int lowestTime = 1000;

class Person {
public:
	int y, x;
	int stairIndex; //계단 번호
	int distanceToStairs; // 계단까지 거리
	int state;

	Person() {
		init();
	}
	void init() {
		state = upFloor;
	}
	void updateState() {
		if (distanceToStairs != 0 && state == upFloor) {
			distanceToStairs--;
		}
		else if (distanceToStairs == 0 && state == upFloor) {
			state = arrivalStair;
		}
		else if (state == arrivalStair) {
			state = waiting;
		}
		else if (state == waiting) {
			state = moving;
		}
	}

};

class Stair {
public:
	int y, x;
	int distance; //계단거리

	int stairN; //계단내려가는 사람 수
	int waitN; //기다리는 사람 수
	int changeN; //시간이 흐르고 아래층도착한 사람 수

	int front; //people_Stair[] 와 people_StairIndex[]의 front
	int rear; //people_Stair[] 와 people_StairIndex[]의 rear
	int frontOrig;
	int stairNOrig;

	int front_wait; //people_waiting[]의 front
	int rear_wait; //people_waiting[]의 rear

	int people_Stair[3]; //계단에 있는 사람들, 각 인덱스의 값은 남은 거리
	int people_StairIndex[3]; //계단에 있는 사람들의 사람 번호
	int people_StairIndexOrig[3];
	int people_waiting[10]; //기다리는 사람들

	Stair() {
		for (int i = 0; i < 3; i++) {
			people_Stair[i] = 0;
			people_StairIndex[i] = 0;
			people_StairIndexOrig[i] = 0;
		}
		front = 0;
		rear = 0;
		front_wait = 0;
		rear_wait = 0;
		stairN = 0;
		waitN = 0;
		changeN = 0;
	}

	int getRealStairIndex(int n) {
		int index;
		index = n % 3;
		return index;
	}
	int getRealWaitingIndex(int n) {
		int index;
		index = n % 10;
		return index;
	}

	//대기줄에 넣는다.
	void pushWaiting(int index) {
		people_waiting[rear_wait] = index;
		rear_wait++;
		rear_wait = getRealWaitingIndex(rear_wait);
		waitN++;
	}

	//대기줄 첫번째 사람을 내려가게 한다.
	void setPerson() {
		people_Stair[rear] = distance;
		people_StairIndex[rear] = people_waiting[front_wait];
		rear++;
		rear = getRealStairIndex(rear);

		people_waiting[front_wait] = 0;
		front_wait++;
		front_wait = getRealWaitingIndex(front_wait);

		stairN++;
		waitN--;
	}

	//현재 상태 검사 하여 사람들을 셋팅한다.
	void pushStairs() {
		while (stairN < 3) {
			if (waitN > 0) 
				setPerson();
			else
				break;
		}
	}

	void updateState() {
		pushStairs();
		changeN = 0;

		frontOrig = front;
		stairNOrig = stairN;

		//계단에 차있는 사람들 수 만큼 1칸씩 내려가게한다.
		for (int i = frontOrig; i < (frontOrig + stairNOrig); i++) {
			int real = getRealStairIndex(i);
			people_Stair[real]--;
			//도착하면
			if (people_Stair[real] == 0) {
				stairN--;
				people_StairIndexOrig[real] = people_StairIndex[real];
				//도착한 동시에 대기줄에 사람있으면 셋팅해줌
				if (waitN > 0)
					setPerson();
				changeN++;
				front = getRealStairIndex(real + 1);
			}
		}
	}


};

Person people[10];
Stair stairs[2];

//계단을 고른다.
void chooseStair(int n, int chose) {
	for (int i = 0; i < n; i++) {
		if ((chose & (1 << i)) != 0) {
			people[i].stairIndex = 1;
			people[i].distanceToStairs = abs(stairs[1].y - people[i].y) + abs(stairs[1].x - people[i].x);
		}
		else {
			people[i].stairIndex = 0;
			people[i].distanceToStairs = abs(stairs[0].y - people[i].y) + abs(stairs[0].x - people[i].x);
		}
	}
}


int calTime(int n) {
	int currN = n; //사람들 
	int real;
	int currTime = 0;

	//다 도착할때까지
	while (currN > 0) {
		currTime++;
		for (int i = 0; i < n; i++) {
			people[i].updateState();
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				if (people[j].state == waiting && people[j].stairIndex == i) {
					stairs[i].pushWaiting(j);
					people[j].state = moving;
				}
			}
			stairs[i].updateState();

			for (int j = stairs[i].frontOrig; j < stairs[i].frontOrig + stairs[i].changeN; j++) {
				real = stairs[i].getRealStairIndex(j);
				people[stairs[i].people_StairIndexOrig[real]].state = arrival;
				//if (stairs[i].people_StairIndexOrig[real] == stairs[i].people_StairIndex[real])
				//	stairs[i].people_StairIndex[real] = 0;
				currN--;
			}
		}
	}

	return currTime;
}

int solve(int n) {
	int result;
	for (int i = 0; i < (1 << n); i++) {
		chooseStair(n, i);
		result = calTime(n);
		if (lowestTime > result)
			lowestTime = result;
		for (int j = 0; j < n; j++)
			people[j].init();
	}

	return lowestTime;
}

int main() {
	int temp;
	int count_p = 0;
	int count_s = 0;

	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &temp);
				if (temp == 1) {
					people[count_p].y = i;
					people[count_p].x = j;
					count_p++;
				}
				else if (temp != 0 && temp != 1) {
					stairs[count_s].y = i;
					stairs[count_s].x = j;
					stairs[count_s].distance = temp;
					count_s++;
				}
			}
		}

		printf("#%d %d\n", tc, solve(count_p));
		count_p = 0;
		count_s = 0;
		lowestTime = 1000;
	}
}
