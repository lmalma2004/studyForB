#include < iostream >

using namespace std;

int T;
int N, K;
int *plashDrive;
int *block;
int *remainBlocks;
bool isRange(int a) {
	if (a < N)
		return true;
	return false;
}
//begin~ end 사이의 drive 배열에서 연속된 block[currK]개의 블록에 wearLevel이하로 놓는다.
bool settingBlock(int begin, const int& end, int currK, int *drive, const int& wearLevel) {
	//if (currK == K)
	//	return true;
	//슬롯에 놓아야할 덩어리의 수가 현재남아있는 슬롯보다 클때 
	//if (remainBlocks[currK] > end - begin)
	//	return false;
	int jump = 0;
	for (int i = begin; i < end-block[currK]+1; i++) {
		bool possible = true;
		for (int j = 0; j < block[currK]; j++) {
			if (drive[i + j] > wearLevel) {
				possible = false;
				jump = j;
				break;
			}
		}
		if (possible) {
			i += block[currK] - 1;
			currK++;
		}
		else {
			i += jump; //이거 안해주면 fail됨
		}
		if (currK == K)
			return true;
	}
	return false;
}

bool isPossible(const int& wearLevel) {
	int begin = 0;
	int end = N;
	if (settingBlock(begin, end, 0, plashDrive, wearLevel))
		return true;
	return false;
}
void makeRemainBlocks() {
	int sum = 0;
	remainBlocks = new int[K];
	for (int i = K-1; i >= 0; i--) {
		sum += block[i];
		remainBlocks[i] = sum;
	}
}
int solve() {
	int max = 0;
	int lo = 0;
	int hi = 200000;

	//makeRemainBlocks();
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (isPossible(mid))
			hi = mid;
		else
			lo = mid;
		//cout << lo << " " << hi << endl;
	}
	return hi;
	
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &K);
		plashDrive = new int[N];
		block = new int[K];

		for (int i = 0; i < N; i++)
			scanf("%d", &plashDrive[i]);
		for (int i = 0; i < K; i++)
			scanf("%d", &block[i]);

		printf("#%d %d\n", tc, solve());
		delete plashDrive;
		delete block;
		delete remainBlocks;
	}
	return 0;
}
