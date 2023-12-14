#include<iostream>

using namespace std;

/*

<<BP<A>>Cd-

*/

struct Node {
	char data;
	Node* prev;
	Node* next;

	Node(char data) :prev(nullptr), next(nullptr), data(data) {};
};

class DoublyLinkedList {
	Node* head;
	Node* tail;
	Node* cursor;

public:
	DoublyLinkedList() :head(nullptr), tail(nullptr), cursor(nullptr) {};

	void Insert(char data) {
		Node* newNode = new Node(data);

		//모두 비어있는 경우 : head와 tail이 없음
		if (head == nullptr && tail == nullptr) {
			head = newNode;
			tail = newNode;
		}
		//맨뒤에 넣는 경우
		else if (cursor == nullptr) {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		//맨앞에 넣는 경우
		else if (cursor == head) {
			newNode->next = cursor;
			cursor->prev = newNode;
			head = newNode;
		}
		
		//서로 다른 데이터 사이에 삽입 경우
		//cursor이전과 cursor 사이에 삽입
		else {
			//이전꺼가 nullptr일 경우 없음
			//그게 맨앞에 대입이니까
			newNode->prev = cursor->prev;
			newNode->next = cursor;
			newNode->prev->next = newNode;
			cursor->prev = newNode;
		}
	}

	void moveLeft() {
		//비어있는 경우 또는 이미 제일 왼쪽일 때 무시
		if (head == nullptr) return;
		if (cursor != nullptr) {
			if (cursor->prev == nullptr) return;
			cursor = cursor->prev;
		}
		else cursor = tail;
	}

	void moveRight()
	{
		//비어있는 경우 또는 이미 제일 오른쪽일 때 무시
		if (head == nullptr || cursor == nullptr) return;
		cursor = cursor->next;
	}

	void BackSpace() {
		//리스트가 비어있는 경우
		if (head == nullptr) return;
		if (cursor == nullptr) {
			tail = tail->prev;
			if (tail == nullptr) head = nullptr;
			else tail->next = nullptr;
			return;
		}

		//이미 제일 왼쪽일 때 무시
		if (cursor->prev == nullptr) return;

		Node* target = cursor->prev;
		
		//target이 head였던 경우
		if (target->prev == nullptr) {
			head = cursor;
			cursor->prev = nullptr;
		}
		else {
			target->prev->next = cursor;
			cursor->prev = target->prev;
		}
		

	}

	void PrintList() {
		Node* pointer = head;
		while (pointer != nullptr) {
			cout << pointer->data;
			pointer = pointer->next;
		}
		cout << "\n";
	}
};

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 0; test < T; test++) {
		string s;
		cin >> s;

		DoublyLinkedList myList;

		for (int i = 0; i < s.size(); i++) {
			char cmd = s[i];
			

			if (cmd == '-') myList.BackSpace();
			else if (cmd == '<') myList.moveLeft();
			else if (cmd == '>') myList.moveRight();
			else {
				myList.Insert(cmd);
			}
		}
		myList.PrintList();
	}

	return 0;

}