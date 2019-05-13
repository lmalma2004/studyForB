#define MAX 30000
#define NULL 0
unsigned int max(unsigned int a, unsigned int b) {
	if (a > b)
		return a;
	return b;
}
void arrClone(int a[4][4], int b[4][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			b[i][j] = a[i][j];
}
void bitToModule(unsigned int bit, int module[4][4]) {
	int cnt = 0;
	for(int i=0; i<4; i++)
		for (int j = 0; j < 4; j++) {
			module[i][j] = bit >> (2 * cnt) & 3;
			cnt++;
		}
}

class Block {
public:
	int bump[4][4];
	int pairBump[4][4];
	int minHeight;
	int maxHeight;
	int base;
	unsigned int bit;
	unsigned int pairBit;
public:
	Block() {
		init();
	}
	void init() {
		base	  = 0;
		bit		  = 0;
		pairBit	  = 0;
	}
public:
	void set(int module[4][4]) {
		setHeightMinAndMax(module);
		base = minHeight;
		makeBump(module, bump, base);
		makePairBump(module, pairBump, maxHeight);
		bit = moduleToBit(bump);
		pairBit = moduleToBit(pairBump);
	}
	void setHeightMinAndMax(int module[4][4]) {
		minHeight = 9;
		maxHeight = 0;
		for(int i=0; i<4; i++)
			for (int j = 0; j < 4; j++) {
				if (minHeight > module[i][j])
					minHeight = module[i][j];
				if (maxHeight < module[i][j])
					maxHeight = module[i][j];
			}
	}
	void makeBump(int module[4][4], int b[4][4], int height) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				b[i][j] = module[i][j] - height;
	}
	void makePairBump(int module[4][4], int b[4][4], int height) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				b[i][j] = height - module[i][j];
		reverse(b);
	}
	unsigned int arrToBit(int module[4][4]) {
		unsigned int ret = 0;
		for(int i=0; i<4; i++)
			for (int j = 0; j < 4; j++) {
				ret |= module[i][j];
				if (i == 3 && j == 3)
					return ret;
				ret = ret << 2;
			}
		
	}
	void rotate(int module[4][4]) {
		int rotateModule[4][4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				rotateModule[i][j] = module[3 - j][i];
		arrClone(rotateModule, module);
	}
	void reverse(int module[4][4]) {
		int reverseModule[4][4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				reverseModule[i][j] = module[i][3 - j];
		arrClone(reverseModule, module);
	}
	unsigned int moduleToBit(int module[4][4]) {
		unsigned int ret = 0;
		for (int i = 0; i < 4; i++) {
			unsigned int currBit = arrToBit(module);
			ret = max(ret, currBit);
			rotate(module);
		}
		return ret;
	}
};

class Node {
public:
	Block b;
	Node* next;
public:
	Node() {
		next = NULL;
	}
};

class LinkedList {
public:
	Node* head;
	Node* rear;
	int size;
public:
	LinkedList() {
		size = 0;
		head = NULL;
		rear = NULL;
	}
	void push(Block b) {
		Node* newNode = new Node();
		newNode->b = b;
		if (head == NULL) {
			head = newNode;
			rear = head;
		}
		else {
			Node* curr = head;
			Node* pre = NULL;
			while (curr->b.base > b.base) {
				pre = curr;
				curr = curr->next;
				if (curr == NULL)
					break;
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
	Node* pop(unsigned int bit) {
		if (size == 0)
			return NULL;

		Node* curr = head;
		Node* pre = NULL;

		while (curr->b.bit != bit) {
			pre = curr;
			curr = curr->next;
			if (curr == NULL)
				return NULL;
		}
		if (pre == NULL)
			head = head->next;
		else
			pre->next = curr->next;
		size--;
		return curr;
	}
};

/*key값이 같다고 bit값이 같은게 아니다.*/
class HashTable {
public:
	static const int TABLE_SIZE = 179799;
	LinkedList table[TABLE_SIZE];
public:
	int hash(unsigned int bit) {
		return bit % TABLE_SIZE;
	}
	void push(Block b) {
		int key = hash(b.bit);
		table[key].push(b);
	}
	Node* pop(unsigned int bit) {
		int key = hash(bit);
		return table[key].pop(bit);
	}
};

Block blocks[MAX];
HashTable hashtable;

int matchBlock() {
	int ret = 0;

	for (int i = 0; i < MAX; i++) {
		Node* block1 = hashtable.pop(blocks[i].bit);
		if (block1 == NULL)
			continue;
		Node* block2 = hashtable.pop(blocks[i].pairBit);
		if (block2 == NULL)
			continue;
		ret += (block1->b.minHeight + block2->b.maxHeight);
		delete block1;
		delete block2;
	}
	return ret;
}

void makeHashTable() {
	for (int i = 0; i < MAX; i++)
		hashtable.push(blocks[i]);
}
void init(int module[][4][4]) {
	for (int i = 0; i < MAX; i++)
		blocks[i].set(module[i]);
}

int makeBlock(int module[][4][4]) {
	int ret;
	init(module);
	makeHashTable();
	return matchBlock();
}
