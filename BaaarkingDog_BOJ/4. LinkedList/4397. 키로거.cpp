#include<iostream>

using namespace std;

//���� �м�

//Ű�ΰŴ� ����ڰ� ���� Ű���� ��� ��� ���
//�齺���̽�, ȭ��ǥ �� ��� �˾Ƴ� �� ����

//T
//������ �Է� : L 
//< > : ȭ��ǥ
//-: �齺���̽�

//�߰��� ������ ���� -> ���Ḯ��Ʈ �������
//ȭ��ǥ ��������� �����ϹǷ� Doubly Linked List �������

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

	//Ŭ���� ������
	DoublyLinkedList() :head(nullptr), tail(nullptr) {
		curNode = head;
	};

	//���� Ŀ�� ��ġ�� ����
	void Insert(char data) {

		Node* newNode = new Node(data);
		//���� �ƹ��͵� ������
		if (head==nullptr||tail == nullptr) {
			head = newNode;
			tail = newNode;
			curNode = newNode->next;
		}
		//�ǵ� ���� ���
		else if (curNode == nullptr) {
			tail->next = newNode; //////////////////////////
			newNode->prev = tail;
			//if (tail != nullptr) {
			//	tail->next = newNode; //////////////////////////
			//	newNode->prev = tail;
			//}
			tail = newNode;
		}
		//�Ǿտ� ���� ���
		else if(curNode->prev==nullptr) {
			head = newNode;
			newNode->next = curNode;
			curNode->prev = newNode;
		}
		//��� ���̿� ���� ���
		else {
			curNode->prev->next = newNode;
			newNode->prev = curNode->prev;
			curNode->prev = newNode;
			newNode->next = curNode;
		}
	}

	//�齺���̽�
	//Ŀ�� �տ� ���� ����
	void BackSpace() {
		if (head == nullptr) return;
		if (tail == nullptr) return;
		if (curNode == nullptr) {
			tail = tail->prev;
			//tail�� head���� ���
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

	//���� ȭ��ǥ
	//Ŀ�� �������� �̵�
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

	//������ ȭ��ǥ
	//Ŀ�� ���������� �̵�
	void MoveRight() {
		//�ƹ��͵� ������ ����
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