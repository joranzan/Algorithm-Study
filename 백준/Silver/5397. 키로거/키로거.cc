#include<iostream>

using namespace std;

//문제 분석

//키로거는 사용자가 누른 키보드 명령 모두 기록
//백스페이스, 화살표 등 모두 알아낼 수 있음

//T
//강산이 입력 : L 
//< > : 화살표
//-: 백스페이스

//중간에 삽입이 많음 -> 연결리스트 사용하자
//화살표 양방향으로 가능하므로 Doubly Linked List 사용하자

string mystring;


struct Node {
	char data;
	Node* prev;
	Node* next;

	Node(char data) : prev(nullptr), next(nullptr), data(data) {};
};

class DoublyLinkedList {
	Node* head;
	Node* tail;
	Node* curNode;

public:

	//클래스 생성자
	DoublyLinkedList() :head(nullptr), tail(nullptr) {
		curNode = head;
	};

	//현재 커서 위치에 삽입
	void Insert(char data) {

		Node* newNode = new Node(data);
		//현재 아무것도 없으면
		if (head==nullptr||tail == nullptr) {
			head = newNode;
			tail = newNode;
			curNode = newNode->next;
		}
		//맨뒤 삽입 경우
		else if (curNode == nullptr) {
			tail->next = newNode; //////////////////////////
			newNode->prev = tail;
			//if (tail != nullptr) {
			//	tail->next = newNode; //////////////////////////
			//	newNode->prev = tail;
			//}
			tail = newNode;
		}
		//맨앞에 삽입 경우
		else if(curNode->prev==nullptr) {
			head = newNode;
			newNode->next = curNode;
			curNode->prev = newNode;
		}
		//노드 사이에 삽입 경우
		else {
			curNode->prev->next = newNode;
			newNode->prev = curNode->prev;
			curNode->prev = newNode;
			newNode->next = curNode;
		}
	}

	//백스페이스
	//커서 앞에 내용 지움
	void BackSpace() {
		if (head == nullptr) return;
		if (tail == nullptr) return;
		if (curNode == nullptr) {
			tail = tail->prev;
			//tail이 head였던 경우
			if (tail == nullptr) {
				head = nullptr;
				return;
			}
			tail->next = nullptr;
			return;
		}
		if (curNode->prev == nullptr) return;
		
		Node* target = curNode->prev;
		curNode->prev = target->prev;
		
		if (curNode->prev == nullptr) head = curNode;
		else target->prev->next = curNode;
	}
	//void BackSpace() {
	//	if (curNode == nullptr) {
	//		if (tail != nullptr) {
	//			tail = tail->prev;
	//			if (tail != nullptr) {
	//				tail->next = nullptr;
	//			}
	//		}
	//	}
	//	else {
	//		Node* target = curNode->prev;
	//		if (target != nullptr) {
	//			curNode->prev = target->prev;
	//			if (curNode->prev != nullptr) {
	//				curNode->prev->next = curNode;
	//			}
	//			else {
	//				head = curNode;
	//			}
	//			delete target;
	//		}
	//	}
	//}

	//왼쪽 화살표
	//커서 왼쪽으로 이동
	void MoveLeft() {
		if (head == nullptr) return;
		if (tail == nullptr) return;

		if (curNode == nullptr) {
			curNode = tail;
			return;
		}
		if (curNode->prev != nullptr) {
			curNode = curNode->prev;
		}
	}

	//오른쪽 화살표
	//커서 오른쪽으로 이동
	void MoveRight() {
		//아무것도 없으면 무시
		if (head == nullptr) return;
		if (tail == nullptr) return;
		if (curNode != nullptr) {
			curNode = curNode->next;
		}
	}

	void Print() {
		Node* cur = head;

		while (cur != nullptr) {
			cout << cur->data;
			cur = cur->next;
		}
		cout << "\n";
	}
	

};

int main() {


	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 0; test < T; test++) {
		
		cin >> mystring;
		DoublyLinkedList myList;

		for (int i = 0; i < mystring.size(); i++) {
			char cmd = mystring[i];

			if (cmd == '-') {
				myList.BackSpace();
			}
			else if (cmd == '<') {
				myList.MoveLeft();
			}
			else if (cmd == '>') {
				myList.MoveRight();
			}
			else {
				myList.Insert(cmd);
			}
		}
		myList.Print();
	}


	return 0;
}