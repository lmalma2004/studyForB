#include <iostream>
 
using namespace std;
 
class LinkedList {
public:
    class Node {
    public:
        int crypto;
        Node* next;
        Node() {
            crypto = 0;
            next = NULL;
        }
        Node(int c) {
            crypto = c;
            next = NULL;
        }
    };
    Node* head;
    Node* rear;
public:
    LinkedList() {
        head = NULL;
        rear = NULL;
    }
    ~LinkedList() {
        while (head != NULL) {
            Node* deleteNode = head;
            head = head->next;
            delete deleteNode;
            deleteNode = NULL;
        }
        head = NULL;
        rear = NULL;
    }
 
    void push_back(int crypto) {
        Node* newNode = new Node(crypto);
        if (head == NULL) {
            head = newNode;
            rear = head;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }
    void insert(int loc, int crypto) {
        Node* newNode = new Node(crypto);
        Node* curr = head;
        Node* pre = NULL;
 
        for (int i = 0; i < loc; i++) {
            pre = curr;
            curr = curr->next;
        }
 
        if (curr == head) {
            newNode->next = head;
            head = newNode;
            return;
        }
        if (curr == NULL) {
            push_back(crypto);
        }
        pre->next = newNode;
        newNode->next = curr;
    }
    void erase(int x) {
        Node* deleteNode = head;
        Node* pre = NULL;
        for (int i = 0; i < x; i++) {
            pre = deleteNode;
            deleteNode = deleteNode->next;
        }
 
        if (deleteNode == head) {
            head = head->next;
            delete deleteNode;
            deleteNode = NULL;
            return;
        }
        if (deleteNode == rear) {
            rear = pre;
            pre->next = NULL;
            delete deleteNode;
            deleteNode = NULL;
            return;
        }
 
        pre->next = deleteNode->next;
        delete deleteNode;
        deleteNode = NULL;
    }
 
    int front() {
        return head->crypto;
    }
    void pop() {
        Node* deleteNode = head;
        head = head->next;
        delete deleteNode;
        deleteNode = NULL;
    }
};
 
int main() {
 
    for (int tc = 1; tc <= 10; tc++) {
        int nOfCrypto;
        int nOfCommand;
        LinkedList list;
        scanf("%d", &nOfCrypto);
        for (int i = 0; i < nOfCrypto; i++) {
            int crypto;
            scanf("%d", &crypto);
            list.push_back(crypto);
        }
 
        scanf("%d", &nOfCommand);
        for (int i = 0; i < nOfCommand; i++) {
            char command;
            scanf(" %c", &command);
            if (command == 'I') {
                int x, y;
                scanf("%d %d", &x, &y);
                int crypto;
                for (int i = 0; i < y; i++) {
                    scanf("%d", &crypto);
                    list.insert(x + i, crypto);
                }
            }
            else if (command == 'D') {
                int x, y;
                scanf("%d %d", &x, &y);
                for (int i = 0; i < y; i++)
                    list.erase(x);
            }
            else if (command == 'A') {
                int y;
                scanf("%d", &y);
                int crypto;
                for (int i = 0; i < y; i++) {
                    scanf("%d", &crypto);
                    list.push_back(crypto);
                }
            }
        }
 
        printf("#%d ", tc);
        for (int i = 0; i < 10; i++) {
            cout << list.front() << " ";
            list.pop();
        }
        cout << endl;
    }
}
