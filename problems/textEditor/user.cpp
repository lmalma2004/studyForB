// 키보드만 사용하는 메모장 프로그램을 만든다.
#define NULL 0
const int DIR_UP = 0;
const int DIR_DOWN = 1;
const int DIR_LEFT = 2;
const int DIR_RIGHT = 3;
const int MAX_N = 700;

class Node {
public:
	Node* next;
	char data;
public:
	Node() {
		next = NULL;
	}
};
class LinkedList {
public:
	Node* head;
	LinkedList* next;
	int size;
public:
	LinkedList() {
		init();
	}
public:
	void clear() {
		while (head != NULL) {
			Node* deleteNode = head;
			head = head->next;
			delete deleteNode;
		}
	}
	void init() {
		next = NULL;
		head = NULL;
		size = 0;
	}
public:
	void insert(int cols, char data) {
		Node* newNode = new Node();
		newNode->data = data;

		if (head == NULL) {
			head = newNode;
		}
		else {
			Node* curr = head;
			Node* pre = NULL;
			for (int i = 0; i < cols; i++) {
				pre = curr;
				curr = curr->next;
			}
			if (pre == NULL) {
				newNode->next = head;
				head = newNode;
			}
			else {
				pre->next = newNode;
				newNode->next = curr;
			}
		}
		size++;
	}
	Node* getChar(int idx) {
		Node* curr = head;
		for (int i = 0; i < idx; i++)
			curr = curr->next;
		return curr;
	}
};

class LinkedListList {
public:
	LinkedList* head;
	int size;
public:
	LinkedListList() {
		init();
	}
public:
	void init() {
		head = new LinkedList();
		size = 1;
	}
	void clear() {
		while (head != NULL) {
			LinkedList* deleteList = head;
			head = head->next;
			deleteList->clear();
		}
		init();
	}
	//rows == 0 이라면 맨앞줄
	void insert(int row, LinkedList* newLine) {
		LinkedList* curr = head;
		LinkedList* pre = NULL;
		for (int i = 0; i < row; i++) {
			pre = curr;
			curr = curr->next;
		}
		if (pre == NULL) {
			newLine->next = curr;
			head = newLine;
		}
		else {
			pre->next = newLine;
			newLine->next = curr;
		}
		size++;
	}
	char getChar(int row, int col) {
		LinkedList* currLine = head;
		for (int i = 0; i < row; i++)
			currLine = currLine->next;
		return currLine->getChar(col)->data;
	}
	LinkedList* getLine(int row) {
		LinkedList* currLine = head;
		for (int i = 0; i < row; i++)
			currLine = currLine->next;
		return currLine;
	}
	LinkedList* getLineColToEnd(int row, int col) {
		LinkedList* currLine = getLine(row);

		Node* currChar = currLine->head;
		for (int i = 0; i < col; i++)
			currChar = currChar->next;
		LinkedList* ret = new LinkedList();

		int cnt = 0;
		while(currChar !=NULL){
			ret->insert(cnt, currChar->data);
			currChar = currChar->next;
			cnt++;
		}
		return ret;
	}
	void deleteStrColToEnd(int row, int col) {
		LinkedList* currLine = head;
		for (int i = 0; i < row; i++)
			currLine = currLine->next;

		Node* currChar = currLine->head;
		Node* preChar = NULL;
		for (int i = 0; i < col; i++) {
			preChar = currChar;
			currChar = currChar->next;
		}
		preChar->next = NULL;
		while (currChar != NULL) {
			Node* deleteNode = currChar;
			currChar = currChar->next;
			delete deleteNode;
			currLine->size--;
		}
	}
};

LinkedListList memoPad;

class Cursor {
public:
	int y;
	int x;
public:
	Cursor() {
		init();
	}
public:
	void init() {
		y = 0;
		x = 0;
	}
	bool isPossible(int direc) {
		if (direc == DIR_UP) {
			if (y == 0)
				return false;
			return true;
		}
		else if (direc == DIR_DOWN) {
			if (y == memoPad.size - 1)
				return false;
			return true;
		}
		else if (direc == DIR_RIGHT) {
			if (y == memoPad.size - 1 && x == memoPad.getLine(y)->size)
				return false;
			return true;
		}
		else if (direc == DIR_LEFT) {
			if (y == 0 && x == 0)
				return false;
			return true;
		}
	}
	void move(int direc) {
		if (direc == DIR_UP && isPossible(DIR_UP)) {
			int nextLineSize = memoPad.getLine(y - 1)->size;
			if (nextLineSize < x)
				x = nextLineSize;
			y--;
		}
		else if (direc == DIR_DOWN && isPossible(DIR_DOWN)) {
			int nextLineSize = memoPad.getLine(y + 1)->size;
			if (nextLineSize < x)
				x = nextLineSize;
			y++;
		}
		else if (direc == DIR_LEFT && isPossible(DIR_LEFT)) {
			if (x == 0) {
				y--;
				x = memoPad.getLine(y)->size;
			}
			else {
				x--;
			}
		}
		else if (direc == DIR_RIGHT && isPossible(DIR_RIGHT)) {
			if (x == memoPad.getLine(y)->size) {
				y++;
				x = 0;
			}
			else {
				x++;
			}
		}
	}
};

Cursor currCursor;
/*
 * 초기화 한다.
 * 문자 입력 공간의 가로와 세로 크기가 n이다.
 * 한 행에 n개의 문자가 들어올 수 있다.
 * 개행문자는 n+1번째 문자로 들어올 수 있다.
 * n개의 행이 존재할 수 있다.
 * 입력 공간을 초과하는 입력은 발생하지 않는다.
 *
 * 예시) n = 3
 * a\n
 * bb\n
 * ccc\n
 * dd\n
 * e
 */
void init(int n) {
	currCursor.init();
	memoPad.clear();
}

/*
 * 현재 커서에 in_char 문자를 삽입한다.
 * 개행문자는 in_char로 입력되지 않는다.
 *
 * aaaaaaa\n
 *    ^
 * 상태에서 'b'를 입력하면,
 *
 * aaabaaaa\n
 *     ^
 * 상태가 된다.
 */
void input_char(char in_char) {
	LinkedList* currLine = memoPad.getLine(currCursor.y);
	currLine->insert(currCursor.x, in_char);
	currCursor.x++;
}

/*
 * 현재 커서에서 개행한다.
 *
 * aaaabbbb\n
 *     ^
 * 이었다면,
 *
 * aaaa\n
 * bbbb\n
 * ^
 * 상태로 바뀐다.
 */
void input_newline() {
	// TODO
	int currLineSize = memoPad.getLine(currCursor.y)->size;

	//맨앞에서 엔터치는 경우
	if (currCursor.x == 0) {
		LinkedList* newLine = new LinkedList();
		memoPad.insert(currCursor.y, newLine);
		currCursor.y++;
	}
	//중간에서 엔터치는 경우
	else if (currCursor.x > 0 && currCursor.x < currLineSize) {
		LinkedList* cutLine = memoPad.getLineColToEnd(currCursor.y, currCursor.x);
		memoPad.deleteStrColToEnd(currCursor.y, currCursor.x);
		memoPad.insert(currCursor.y + 1, cutLine);
		currCursor.x = 0;
		currCursor.y++;
	}
	//맨끝에서 엔터치는 경우
	else if (currCursor.x == currLineSize) {
		LinkedList* newLine = new LinkedList();
		memoPad.insert(currCursor.y + 1, newLine);
		currCursor.x = 0;
		currCursor.y++;
	}

}
/*
 * 상하좌우로 움직인다.
 *
 * 메모장에
 * aaaaa
 * bbb
 * cccccccc
 * ddddd
 * 로 입력하고 마구마구 움직여보자.
 *
 * 못움직이는 경우와 상하 이동시에 줄 길이가 다를 떄 커서의 위치 변화를 잘 관찰해서 구현하라.
 */
 // 0: Up, 1: Down, 2: Left, 3: Right
void move_cursor(int direction) {
	currCursor.move(direction);
}
/*
 * row 행, column 열에 있는 문자를 얻는다.
 * 행열번호는 1행 1열부터 시작한다.
 * 참조할 수 없는 행열은 입력으로 주어지지 않는다.
 */
char get_char(int row, int column) {
	return memoPad.getChar(row - 1, column - 1);
}

