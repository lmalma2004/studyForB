#define NULL  0
#define UP	  0
#define DOWN  1
#define LEFT  2
#define RIGHT 3
//0: Up, 1 : Down, 2 : Left, 3 : Right
class MemoPad {
public:
	class Cursor {
	public:
		int y;
		int x;
	public:
		Cursor() {
			init();
		}
		void init() {
			y = 0;
			x = 0;
		}
		void moveUp() {
			y--;
		}
		void moveDown() {
			y++;
		}
		void moveRight() {
			x++;
		}
		void moveLeft() {
			x--;
		}
	};
	class Line {
	public:
		class Char {
		public:
			char c;
			Char* next;
			Char* pre;
			Char() {
				init();
			}
			Char(char ch) {
				c = ch;
				next = NULL;
				pre = NULL;
			}
			void init() {
				c = '\0';
				next = NULL;
				pre = NULL;
			}
		};
		Char* head;
		Char* rear;
		Line* next;
		Line* pre;
		int lineSize;
	public:
		Line() {
			head = NULL;
			rear = NULL;
			next = NULL;
			pre = NULL;
			lineSize = 0;
		}
		void init() {
			if (head == NULL)
				return;
			while (head != NULL) {
				Char* deleteNode = head;
				head = head->next;
				delete deleteNode;
				deleteNode = NULL;
			}
			head = NULL;
			rear = NULL;
			next = NULL;
			pre = NULL;
			lineSize = 0;
		}
		void append(int x, char c) {
			Char* newChar = new Char(c);
			if (head == NULL || x == lineSize) {
				push_back(c);
				return;
			}
			Char* curr = head;
			for (int i = 0; i < x; i++)
				curr = curr->next;

			if (curr == head) {
				newChar->next = head;
				head->pre = newChar;
				head = newChar;
				lineSize++;
				return;
			}
			newChar->pre = curr->pre;
			newChar->next = curr;
			curr->pre->next = newChar;
			curr->pre = newChar;
			lineSize++;
		}
		void push_back(char c) {
			if (head == NULL) {
				head = new Char(c);
				rear = head;
				lineSize++;
				return;
			}
			Char* newChar = new Char(c);
			newChar->pre = rear;
			rear->next = newChar;
			rear = newChar;
			lineSize++;
		}
		char getChar(int x) {
			if (x == 0)
				return head->c;
			if (x == lineSize - 1)
				return rear->c;

			Char* currChar = head;
			for (int i = 0; i < x; i++)
				currChar = currChar->next;
			return currChar->c;
		}
		Line* getString(int x) {
			Char* currChar = head;
			for (int i = 0; i < x; i++) {
				currChar = currChar->next;
			}
			Line* ret = new Line();
			while (currChar != NULL) {
				ret->push_back(currChar->c);
				currChar = currChar->next;
			}
			return ret;
		}
		void removeString(int x) {
			if (x == lineSize)
				return;
			if (x == 0) {
				while (head != NULL) {
					Char* deleteNode = head;
					head = head->next;
					delete deleteNode;
					deleteNode = NULL;
				}
				head = NULL;
				rear = NULL;
				lineSize = x;
				return;
			}
			//rear만 삭제하는경우
			if (x == lineSize - 1) {
				Char* deleteChar = rear;
				rear = rear->pre;
				rear->next = NULL;
				delete deleteChar;
				deleteChar = NULL;
				lineSize = x;
				return;
			}
			Char* currChar = head;
			for (int i = 0; i < x; i++)
				currChar = currChar->next;
			Char* preChar = currChar->pre;
			rear = preChar;
			rear->next = NULL;

			while (currChar != NULL) {
				Char* deleteChar = currChar;
				currChar = currChar->next;
				delete deleteChar;
				deleteChar = NULL;
			}
			lineSize = x;
		}
	};	
public:
	Cursor cursor;
	Line* head;
	Line* rear;
	int padSize;
	int maxSize;
public:
	MemoPad() {
		head = NULL;
		rear = NULL;
		maxSize = 0;
		padSize = 0;
	}
	void init(int n) {
		if (head == NULL) {
			maxSize = n;
			return;
		}
		while (head != NULL) {
			Line* deleteNode = head;
			head = head->next;
			deleteNode->init();
			delete deleteNode;
			deleteNode = NULL;
		}
		cursor.init();
		padSize = 0;
		maxSize = n;
		head = NULL;
		rear = NULL;
	}
	Line* getLine(int y) {
		if (y == 0)
			return head;
		if (y == padSize)
			return rear;

		Line* currLine = head;
		for (int i = 0; i < y; i++)
			currLine = currLine->next;
		return currLine;
	}
	void input_char(char in_char) {
		if (head == NULL) {
			head = new Line();
			rear = head;
		}
		Line* currLine = getLine(cursor.y);
		currLine->append(cursor.x, in_char);
		move_cursor(RIGHT);
	}
	void input_newline() {
		Line* currLine = getLine(cursor.y);
		Line* newLine = new Line();
		
		//라인의 맨뒤 엔터
		if (cursor.x == currLine->lineSize) {
			newLine->pre = currLine;
			newLine->next = currLine->next;
			if (currLine->next != NULL)
				currLine->next->pre = newLine;
			else
				rear = newLine;
			currLine->next = newLine;
			padSize++;
			cursor.x = 0;
			move_cursor(DOWN);
			return;
		}
		//라인의 맨앞 엔터
		if (cursor.x == 0) {
			newLine->next = currLine;
			newLine->pre = currLine->pre;
			if (currLine->pre != NULL)
				currLine->pre->next = newLine;
			else
				head = newLine;
			currLine->pre = newLine;
			padSize++;
			cursor.x = 0;
			move_cursor(DOWN);
			return;
		}

		//라인의 중간 엔터
		newLine = currLine->getString(cursor.x);
		currLine->removeString(cursor.x);
		newLine->next = currLine->next;
		newLine->pre = currLine;
		if (currLine->next != NULL)
			currLine->next->pre = newLine;
		else
			rear = newLine;
		currLine->next = newLine;
		padSize++;
		cursor.x = 0;
		move_cursor(DOWN);
	}
	void move_cursor(int direction) {
		if (direction == UP) {
			if (cursor.y == 0)
				return;
			Line* currLine = getLine(cursor.y);
			Line* preLine = currLine->pre;
			if (cursor.x > preLine->lineSize) 
				cursor.x = preLine->lineSize;
			cursor.moveUp();
		}
		else if (direction == DOWN) {
			if (cursor.y == padSize)
				return;
			if (cursor.y == maxSize)
				return;
			Line* currLine = getLine(cursor.y);
			Line* nextLine = currLine->next;
			if (cursor.x > nextLine->lineSize)
				cursor.x = nextLine->lineSize;
			cursor.moveDown();
		}
		else if (direction == LEFT) {
			Line* currLine = getLine(cursor.y);
			Line* preLine = currLine->pre;
			if (cursor.x == 0 && cursor.y > 0) {
				cursor.x = preLine->lineSize;
				cursor.moveUp();
				return;
			}
			if (cursor.x == 0) {
				return;
			}
			cursor.moveLeft();
		}
		else if (direction == RIGHT) {
			Line* currLine = getLine(cursor.y);
			Line* nextLine = currLine->next;
			if (cursor.x == currLine->lineSize && cursor.y < padSize) {
				cursor.x = 0;
				cursor.moveDown();
				return;
			}
			if (cursor.x == currLine->lineSize) {
				return;
			}
			cursor.moveRight();
		}

	}
	char get_char(int row, int column) {
		Line* currLine = getLine(row - 1);
		return currLine->getChar(column - 1);
	}
};
MemoPad memoPad;

void init(int n) {
	//각 테스트 케이스의 초기에 입력된다.
	//초기 커서의 위치는 1, 1 이다.
	//n 은 텍스트 에디터의 N 을 나타낸다.
	memoPad.init(n);
}

void input_char(char in_char) {
	//in_char 에 입력된 문자를 현재 커서 위치에 입력한다.
	//	입력 뒤에 커서는 오른쪽으로 한 칸 이동한다.
	//	문자는 한 행에 최대 N 개 까지 입력된다.
	memoPad.input_char(in_char);
}

void input_newline() {
	//현재 커서 위치에 엔터를 입력한다.
	//	현재 커서가 R 행이라면(R + 1, 1) 으로 이동한다.
	//	엔터는 최대 N - 1 번 입력된다.
	memoPad.input_newline();
}

void move_cursor(int direction) { 
	//0: Up, 1 : Down, 2 : Left, 3 : Right
	//	커서를 위아래 좌우로 이동한다.
	//	커서는 입력된 텍스트 안에서만 이동된다.
	//	이동 될 수 없는 곳으로 이동시키는 명령일 경우 무시한다.
	//	즉, 현재 위치에 그대로 있는다.
	memoPad.move_cursor(direction);
}

char get_char(int row, int column) {
	//(row, column) 위치에 있는 문자를 반환한다.
	//	위치는 항상 문자가 있는 위치이다.
	//	엔터는 문자가 아니다.
	return memoPad.get_char(row, column);
}

