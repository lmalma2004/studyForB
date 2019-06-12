#include <iostream>
#include <queue>
//prefix : 접두사
//suffix : 접미사

using namespace std;
int mstrlen(char* str) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}
void mstrcpy(char* copy, char* orig) {
	int len = 0;
	while (orig[len] != '\0') {
		copy[len] = orig[len];
		len++;
	}
	copy[len] = '\0';
}
char* mstrmerge(char* orig, char add) {
	int len = mstrlen(orig);
	char* ret = new char[len + 2];
	mstrcpy(ret, orig);
	ret[len] = add;
	ret[len + 1] = '\0';
	return ret;
}
int mstrcmp(char* str1, char* str2) {
	int len1 = mstrlen(str1);
	int len2 = mstrlen(str2);
	int len = 0;
	for (int i = 0; i < len1; i++) {
		if (str1[i] < str2[i])
			return 1;
		else if (str1[i] > str2[i])
			return -1;
	}
	return 0;
}

class pqForNode {
public:
	char* word;
	int priority;
	pqForNode() {
		word = NULL;
		priority = 0;
	}
	pqForNode(char* w, int pri) {
		int len = mstrlen(w);
		word = new char(len + 1);
		mstrcpy(word, w);
		priority = pri;
	}
};

class compare {
public:
	bool operator()(const pqForNode& n1, const pqForNode& n2) {
		if (n1.priority == n2.priority) {
			int cmp = mstrcmp(n1.word, n2.word);
			if (cmp < 0)
				return true;
			else
				return false;
		}
		return n1.priority < n2.priority;
	}
};

class priority_queue_my {
public:
	static const int MAX_SIZE = 1000;
	pqForNode heap[MAX_SIZE];
	int heapSize;
public:
	priority_queue_my() {
		heapSize = 0;
	}
	bool compare_my(const pqForNode& n1, const pqForNode& n2) {
		if (n1.priority == n2.priority) {
			int cmp = mstrcmp(n1.word, n2.word);
			if (cmp < 0)
				return true;
			else
				return false;
		}
		return n1.priority < n2.priority;
	}
	void push(pqForNode newNode) {
		if (heapSize + 1 > MAX_SIZE)
		{
			printf("queue is full!");
			return;
		}

		heap[heapSize] = newNode;

		int current = heapSize;
		while (current > 0 && !compare_my(heap[current], heap[(current - 1) / 2]))
		{
			pqForNode temp = heap[(current - 1) / 2];
			heap[(current - 1) / 2] = heap[current];
			heap[current] = temp;
			current = (current - 1) / 2;
		}

		heapSize = heapSize + 1;
	}
	void pop() {
		if (heapSize <= 0)
		{
			return;
		}
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
				child = !compare_my(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
			}

			if (heap[current].priority > heap[child].priority)
			{
				break;
			}

			pqForNode temp = heap[current];
			heap[current] = heap[child];
			heap[child] = temp;

			current = child;
		}
	}
	pqForNode top() {
		return heap[0];
	}
	int size() {
		return heapSize;
	}
};

class Node {
public:
	Node* next[26];
	int priority;
	Node() {
		for (int i = 0; i < 26; i++)
			next[i] = NULL;
		priority = 0;
	}
	void setWord(char* word) {
		char curr = word[0];
		if (curr == '\0') {
			upPriority();
			return;
		}

		int idx = curr - 'a';
		if (next[idx] == NULL)
			next[idx] = new Node();
		next[idx]->setWord(word + 1);
	}
	Node* getPrefixNode(char* prefix) {
		char curr = prefix[0];
		if (curr == '\0') {
			return this;
		}
		int idx = curr - 'a';
		return next[idx]->getPrefixNode(prefix + 1);
	}
	void upPriority() {
		priority++;
	}
	//void getAllWords(char* prefix, priority_queue<pqForNode, vector<pqForNode>, compare>& pq) {
	void getAllWords(char* prefix, priority_queue_my& pq) {
		if (priority > 0) {
			pqForNode newNode(prefix, priority);
			pq.push(newNode);
		}
		for (int i = 0; i < 26; i++) {
			if (next[i] != NULL) {
				char* nextPrefix = mstrmerge(prefix, 'a' + i);
				next[i]->getAllWords(nextPrefix, pq);
			}
		}
	}
};


class Trie {
public:
	Node* root;
	Trie() {
		root = NULL;
	}
	void insert(char* word) {
		/*word를 Trie에 삽입한다.*/
		if (root == NULL)
			root = new Node();
		root->setWord(word);
	}
	int AutoCompleteWord(char* prefix, char* arr[5]) {
		/*prefix로 검색했을때 자동완성된 단어들중 5개를 arr에 넣는다.
		  자동완성된 단어들의 개수를 반환한다. (0~5) */
		Node* prefixNode = root->getPrefixNode(prefix);
		//priority_queue<pqForNode, vector<pqForNode>, compare> pq;
		priority_queue_my pq;
		prefixNode->getAllWords(prefix, pq);
		int size = pq.size();
		for (int i = 0; i < size; i++) {
			if (i >= 5)
				return size;
			arr[i] = new char[mstrlen(pq.top().word) + 1];
			mstrcpy(arr[i], pq.top().word);
			pq.pop();
		}
		return size;
	}

};

Trie trie;

int main() {
	for (int i = 0; i < 1000; i++) {
		char tmp[25];
		scanf(" %s", tmp);
		trie.insert(tmp);
	}
	char q[3] = { 't','a','\0' };
	char* arr[5];

	int cnt = trie.AutoCompleteWord(q, arr);

	for (int i = 0; i < cnt; i++) 
		cout << arr[i] << endl;
	return 0;
}
