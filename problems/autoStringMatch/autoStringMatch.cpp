#include < iostream >

using namespace std;

int strlen(char* s) {
	int len = 0;
	while (*s != '\0') {
		len++;
		*s++;
	}
	return len;
}

char* strMerge(char* orig, char add) {
	int size = strlen(orig);
	char* ret = new char[size + 2];
	for (int i = 0; i < size; i++) {
		ret[i] = orig[i];
	}
	ret[size] = add;
	ret[size + 1] = '\0';
	return ret;
}

class Node {
public:
	Node* next[26];
	int priority;
public:
	Node() {
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
		priority = 0;
	}
public:
	void upPriority() {
		priority++;
	}
	void downPriority() {
		priority--;
	}
};

class NodeForQueue {
public:
	char* str;
	int priority;
};

class PriorityQueue {
public:
	NodeForQueue heap[1000];
	int size_;
public:
	PriorityQueue() {
		size_ = 0;
	}
	void swap(int a, int b) {
		NodeForQueue tmp = heap[a];
		heap[a] = heap[b];
		heap[b] = tmp;
	}
	void push(NodeForQueue n) {
		heap[size_] = n;
		int parent = (size_ - 1) / 2;
		int child = size_;
		while (child != 0) {
			if (heap[child].priority > heap[parent].priority) {
				swap(child, parent);
				child = parent;
				parent = (child - 1) / 2;
			}
			else if (heap[child].priority == heap[parent].priority) {
				int cmp = strcmp(heap[child].str, heap[parent].str);
				if (cmp < 0) {
					swap(child, parent);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break; //여기안해주면 무한루프
			}
			else
				break;
		}
		size_++;
	}
	void pop() {
		size_--;
		heap[0] = heap[size_];
		int parent = 0;
		int leftChild = 1;
		int rightChild = 2;
		int child;

		while (size_ > rightChild) {

			if (heap[leftChild].priority > heap[rightChild].priority) {
				child = leftChild;
			}
			else if (heap[leftChild].priority == heap[rightChild].priority) {
				int cmp = strcmp(heap[leftChild].str, heap[rightChild].str);
				if (cmp < 0)
					child = leftChild;
				else
					child = rightChild;
			}

			if (heap[parent].priority < heap[child].priority) {
				swap(parent, child);
				parent = child;
				leftChild = parent * 2 + 1;
				rightChild = parent * 2 + 2;
			}
			else if (heap[parent].priority == heap[child].priority) {
				int cmp = strcmp(heap[parent].str, heap[child].str);
				if (cmp > 0) {
					swap(parent, child);
					parent = child;
					leftChild = parent * 2 + 1;
					rightChild = parent * 2 + 2;
				}
				else
					break; //여기안해주면 무한루프
			}
			else {
				break;
			}
		}

		//마지막 parent의 자식이 1개인경우 (leftChild임)
		child = parent * 2 + 1; 
		if (child == size_ - 1) {
			if (heap[parent].priority < heap[child].priority) {
				swap(parent, child);
			}
			else if (heap[parent].priority == heap[child].priority) {
				int cmp = strcmp(heap[parent].str, heap[child].str);
				if (cmp > 0) {
					swap(parent, child);
				}
			}
		}

	}
	NodeForQueue top() {
		return heap[0];
	}
	int size() {
		return size_;
	}
};
class compare {
public:
	bool operator()(const NodeForQueue& n1, const NodeForQueue& n2) {
		if (n1.priority == n2.priority) {
			int cmp = strcmp(n1.str, n2.str);
			if (cmp > 0)
				return true;
			else
				return false;
		}
		return n1.priority < n2.priority;
	}
};
//priority_queue< NodeForQueue, vector< NodeForQueue >, compare > pq;
PriorityQueue pq;

class Trie {
public:
	Node* root;
public:
	Trie() {
		root = NULL;
	}
public:
	int toNumber(char c) {
		return c - 'a';
	}
	char toChar(int n) {
		return n + 'a';
	}
	void findAndPush(char* prefix, Node* curr, 
		PriorityQueue& pq) {
		if (curr->priority > 0) {
			NodeForQueue tmp;
			tmp.priority = curr->priority;
			tmp.str = prefix;
			pq.push(tmp);
		}
		for (int i = 0; i < 26; i++) {
			if (curr->next[i] != NULL) {
				char nextChar = toChar(i);
				findAndPush(strMerge(prefix, nextChar), curr->next[i], pq);
			}
		}
	}
	//접두사가 q인 단어들 arr에 저장
	//root를 q의 마지막단어로하는 트리에서 존재하는 단어들을 리턴해준다.
	int findAll(char* q, char* arr[5]) {
		Node* curr = root;
		char* prefix = q;

		while (*q != '\0') {
			int current = toNumber(*q);
			if (curr->next[current] == NULL)
				return 0;
			curr = curr->next[current];
			*q++;
		}

		if (curr->priority > 0) {
			NodeForQueue tmp;
			tmp.priority = curr->priority;
			tmp.str = prefix;
			pq.push(tmp);
		}

		for (int i = 0; i < 26; i++) {
			if (curr->next[i] != NULL) {
				char nextChar = toChar(i);
				findAndPush(strMerge(prefix, nextChar), curr->next[i], pq);
			}
		}

		int count = pq.size() < 5 ? pq.size() : 5;
		for (int i = 0; i < count; i++) {
			arr[i] = pq.top().str;
			cout << pq.top().priority << endl;
			pq.pop();
		}
		return count;
	}
	void insertStr(char* s) {
		if (root == NULL)
			root = new Node();
		Node* curr = root;
		while (*s != '\0') {
			int current = toNumber(*s);
			if (curr->next[current] == NULL)
				curr->next[current] = new Node();
			curr = curr->next[current];
			*s++;
		}
		curr->upPriority();
	}
	bool isExist(char* s) {
		Node* curr = root;
		while (*s != '\0') {
			int current = toNumber(*s);
			if (curr->next[current] == NULL)
				return false;
			curr = curr->next[current];
			*s++;
		}
		return curr->priority > 0;
	}
};

Trie trie;

int main() {
	for (int i = 0; i < 1000; i++) {
		char tmp[25];
		scanf(" %s", tmp);
		trie.insertStr(tmp);
	}
	char q[3] = { 't','a','\0' };
	char* arr[5];

	int cnt = trie.findAll(q, arr);

	for (int i = 0; i < cnt; i++) {
		cout << arr[i] << endl;
	}
	return 0;
}
