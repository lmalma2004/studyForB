#include < iostream >

using namespace std;

void strcpy(char data[], char copy[]) {
	int curr = 0;
	while (copy[curr] != '\0') {
		data[curr] = copy[curr];
		curr++;
	}
	data[curr] = '\0';
}

class Node {
public:
	char data[7];
	Node* next;
	Node() {
		init();
	}
	void init() {
		for (int i = 0; i < 7; i++)
			data[i] = '\0';
		next = NULL;
	}
	void setData(char n[]) {
		strcpy(data, n);
	}
	void setNext(Node* n) {
		next = n;
	}
};

class LinkedList {
public:
	Node* head;
	Node* rear;
	LinkedList() {
		head = NULL;
		rear = NULL;
	}
	~LinkedList() {
		//deleteNode();
	}
	void deleteNode() {
		Node* curr = head;

		while (curr != NULL) {

			Node* next = curr->next;
			delete curr;
			curr = next;
		}

		head = NULL;
		rear = NULL;
	//	if (head == NULL)
	//		return;
	//	Node* curr = head;
	//	Node* next = head->next;
	//	while (curr->next != NULL) {
	//		delete curr;
	//		curr = next;
	//		next = curr->next;
	//	}
	//	delete curr;
	//	delete next;
	}
public:
	void push(char number[]) {
		if (head == NULL) {
			head = new Node();
			head->setData(number);
			rear = head;
		}
		else {
			Node* curr = head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			Node* newNode = new Node();
			newNode->setData(number);
			curr->setNext(newNode);
			rear = curr->next;
		}
	}

	void delete_(int loc, int count) {
		Node* curr = head;
		Node* pre;
		if (loc == 0) {
			for (int i = 0; i < count; i++) {
				Node* next = curr->next;
				delete curr;
				curr = next;
			}
			head = curr;
		}
		else {
			for (int i = 0; i < loc; i++) {
				pre = curr;
				curr = curr->next;
			}

			for (int i = 0; i < count; i++) {
				Node* next = curr->next;
				delete curr;
				curr = next;
			}
			pre->next = curr;
		}
	}

	void insert(int loc, char number[]) {
		Node* newNode = new Node();
		newNode->setData(number);

		if (loc == 0) {
			newNode->next = head;
			head = newNode;
			rear = newNode->next;
		}
		else {
			Node* curr = head;
			for (int i = 1; i < loc; i++)
				curr = curr->next;
			if (curr->next == NULL)
				rear = newNode;

			newNode->next = curr->next;
			curr->next = newNode;
		}
	}

	void print() {
		Node* curr = head;
		while (curr != NULL) {
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}
};

void insertLL(LinkedList& a, LinkedList& b, int loc) {
	if (loc == 0) {
		b.rear->next = a.head;
		a.head = b.head;
	}
	else {
		Node* curr = a.head;
		for (int i = 1; i < loc; i++)
			curr = curr->next;
		if (curr == a.rear) {
			a.rear->next = b.head;
			a.rear = b.rear;
		}
		else {
			b.rear->next = curr->next;
			curr->next = b.head;
		}
	}

}

void addLL(LinkedList& a, LinkedList& b) {
	if (a.rear == NULL) {
		a.head = b.head;
		a.rear = b.rear;
	}
	else {
		a.rear->next = b.head;
		a.rear = b.rear;
	}
}

int T, N, M;
LinkedList list;

int main() {
	for (int tc = 1; tc <= 10; tc++) {
		scanf("%d", &N);
		list.head = NULL;
		list.rear = NULL;
		for (int i = 0; i < N; i++) {
			char tmp[7];
			scanf("%s", tmp);
			list.push(tmp);
		}
		scanf("%d", &M);

		LinkedList add[500];
		for (int i = 0; i < M; i++) {
			int x, y;
			char tmp;
			char n[7];
			scanf(" %c", &tmp);
			if (tmp == 'I') {

				scanf("%d %d", &x, &y);

				for (int j = 0; j < y; j++) {
					scanf("%s", n);
					add[i].push(n);
				}
				insertLL(list, add[i], x);
			}
			else if (tmp == 'D') {

				scanf("%d %d", &x, &y);

				list.delete_(x, y);
			}
			else if (tmp == 'A') {
				scanf("%d", &y);
				for (int j = 0; j < y; j++) {
					scanf("%s", n);
					add[i].push(n);
				}
				addLL(list, add[i]);
			}

		}

		Node* curr = list.head;
		printf("#%d ", tc);
		for (int i = 0; i < 10; i++) {
			printf("%s ", curr->data);
			curr = curr->next;
		}

		cout << endl;
	}
}
