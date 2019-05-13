#include < iostream >
#define SPADE 'S'
#define DIAMOND 'D'
#define CLUB 'C'
#define HEART 'H'
static const int Top			= 0;
static const int OnePair		= 1;
static const int TwoPair		= 2;
static const int Triple			= 3;
static const int Straight		= 4;
static const int Flush			= 5;
static const int FullHouse		= 6;
static const int FourCard		= 7;
static const int StraightFlush	= 8;

using namespace std;
int T;

class CardsNumberCount {
public:
	long long countInfo;
	long long countOnlyOne;
	CardsNumberCount() {
		init();
	}
	void init() {
		countInfo = 0;
		countOnlyOne = 0;
	}
public:
	void push(int number) {

		int loc = (number - 1) * 3;
		if (number == 1) {
			long long loc = (1LL << (13 * 3));
			countInfo += loc;
			countOnlyOne |= loc;
		}
		countInfo += (1LL << loc);
		countOnlyOne |= (1LL << loc);

	}
	int countNumber(int number) {
		int loc = (number) * 3;
		return (7 & (countInfo >> loc));
	}
	int getMax() {
		int max = 0;
		for (int i = 0; i < 13; i++) {

			long long curr = countNumber(i);
			if (max < curr)
				max = curr;
		}
		return max;
	}
};

class CardsShapeCount {
public:
	int countInfo;
	int spadeNumber[7];
	int spadeC;
	int diamondNumber[7];
	int diamondC;
	int clubNumber[7];
	int clubC;
	int heartNumber[7];
	int heartC;
	char maxShape;

	CardsShapeCount() {
		init();
	}

	void init() {
		countInfo = 0;
		spadeC = 0;
		diamondC = 0;
		clubC = 0;
		heartC = 0;
	}
public:
	int getBitLocation(char shape) {
		if (shape == SPADE)
			return 0;
		else if (shape == DIAMOND)
			return 3;
		else if (shape == CLUB)
			return 6;
		else if (shape == HEART)
			return 9;
	}
	void push(char shape, int number) {
		countInfo += (1 << getBitLocation(shape));
		if (shape == SPADE) {
			spadeNumber[spadeC] = number;
			spadeC++;
		}
		else if (shape == CLUB) {
			clubNumber[clubC] = number;
			clubC++;
		}
		else if (shape == DIAMOND) {
			diamondNumber[diamondC] = number;
			diamondC++;
		}
		else if (shape == HEART) {
			heartNumber[heartC] = number;
			heartC++;
		}
	}
	int countShape(char shape) {
		return 7 & (countInfo >> getBitLocation(shape));
	}
	int getNumber(int index, char shape) {
		if (shape == SPADE) {
			return spadeNumber[index];
		}
		else if (shape == DIAMOND) {
			return diamondNumber[index];
		}
		else if (shape == CLUB) {
			return clubNumber[index];
		}
		else if (shape == HEART) {
			return heartNumber[index];
		}
	}
	int getMax() {
		int sCount = countShape(SPADE);
		int cCount = countShape(CLUB);
		int hCount = countShape(HEART);
		int dCount = countShape(DIAMOND);

		int max = sCount;
		maxShape = SPADE;
		if (max < cCount) {
			max = cCount;
			maxShape = CLUB;
		}
		if (max < hCount) {
			max = hCount;
			maxShape = HEART;
		}
		if (max < dCount) {
			max = dCount;
			maxShape = DIAMOND;
		}
		return max;
	}
};

CardsNumberCount numberC;
CardsShapeCount shapeC;

bool isTriple() {
	for (int i = 0; i < 13; i++) {
		if (numberC.countNumber(i) == 3)
			return true;
	}
	return false;
}
bool isTwoTriple() {
	int cnt = 0;
	for (int i = 0; i < 13; i++) {
		if (numberC.countNumber(i) == 3)
			cnt++;
		if (cnt >= 2)
			return true;
	}
	return false;
}
bool isTwoPair() {
	int cnt = 0;
	for (int i = 0; i < 13; i++) {
		if (numberC.countNumber(i) == 2)
			cnt++;
		if (cnt >= 2)
			return true;
	}
	return false;
}

bool isOnePair() {
	for (int i = 0; i < 13; i++) {
		if (numberC.countNumber(i) == 2)
			return true;
	}
	return false;
}

bool isFlush() {
	if (shapeC.getMax() >= 5)
		return true;
	return false;
}

bool isStraight() {
	static long long STRAIGHTBIT = 4681;
	int index;
	if (numberC.countNumber(0) >= 1)
		index = 10;
	else
		index = 9;

	for (int i = 0; i < index; i++) {
		long long curr = (numberC.countOnlyOne >> (3 * i));
		if ((curr & STRAIGHTBIT) == STRAIGHTBIT)
			return true;
	}
	return false;
}

bool isFourCard() {
	if (numberC.getMax() == 4)
		return true;
	return false;
}

bool isFullHouse() {
	if (isTriple() && isOnePair())
		return true;
	if (isTwoTriple())
		return true;
	return false;
}

bool isPossible(int score) {
	if (score == StraightFlush) {
		if (isFlush()) {

			long long cards = 0;
			for (int i = 0; i < shapeC.getMax(); i++) {
				int number = shapeC.getNumber(i, shapeC.maxShape);
				if (number == 1) {
					long long loc = 1LL << (13 * 3);
					cards |= loc;
				}
				cards |= 1LL << (3 * (shapeC.getNumber(i, shapeC.maxShape)-1));
			}
			static long long STRAIGHTBIT2 = 4681;

			for (int i = 0; i < 10; i++) {
				long long curr = (cards >> (3 * i));
				if ((curr & STRAIGHTBIT2) == STRAIGHTBIT2)
					return true;
			}
		}
	}
	else if (score == FourCard) {
		if(isFourCard())
			return true;
	}
	else if (score == FullHouse) {
		if (isFullHouse())
			return true;
	}
	else if (score == Flush) {
		if (isFlush())
			return true;
	}
	else if (score == Straight) {
		if (isStraight())
			return true;
	}
	else if (score == Triple) {
		if (isTriple())
			return true;
	}
	else if (score == TwoPair) {
		if (isTwoPair())
			return true;
	}
	else if (score == OnePair) {
		if (isOnePair())
			return true;
	}
	else if (score == Top) {
		return true;
	}

	return false;
}

int solve() {
	for (int i = StraightFlush; i >= Top; i--) {
		if (isPossible(i))
			return i;
	}
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		for (int i = 0; i < 7; i++) {
			char m;
			int n;
			scanf(" %c %d", &m, &n);

			numberC.push(n);
			shapeC.push(m, n);
		}
		int ret = solve();
		if (ret == StraightFlush)
			printf("#%d Straight Flush\n", tc);
		else if (ret == FourCard)
			printf("#%d 4 Card\n", tc);
		else if (ret == FullHouse)
			printf("#%d Full House\n", tc);
		else if (ret == Flush)
			printf("#%d Flush\n", tc);
		else if (ret == Straight)
			printf("#%d Straight\n", tc);
		else if (ret == Triple)
			printf("#%d Triple\n", tc);
		else if (ret == TwoPair)
			printf("#%d 2 Pair\n", tc);
		else if (ret == OnePair)
			printf("#%d 1 Pair\n", tc);
		else
			printf("#%d Top\n", tc);
		numberC.init();
		shapeC.init();
	}
	return 0;
}

