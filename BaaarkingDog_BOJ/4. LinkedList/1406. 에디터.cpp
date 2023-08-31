#include<iostream>
#include<vector>

using namespace std;

struct Node {
	char data;
	int prev;
	int next;
};

int main() {

	string s;   //���� 10�� ����
	cin >> s;
	int length = s.size();  //���� Ŀ���� length +1 ���� ����

	int Q;  //��ɾ� ���� 50������
	cin >> Q;

	

	vector<Node> node(length);

	//��������Ʈ ���� �迭 �����
	for (int i = 0; i < length; i++) {
		node[i].data = s[i];
		node[i].prev = i - 1;
		node[i].next = i + 1;

		if (i <= 0) {
			node[i].prev = -1;
		}
	}
	//��ɾ�� ����
	int cursor = length ;  //end()
	node.push_back({ NULL, length-1,-1 });
 

	for (int i = 0; i < Q; i++) {
		char Query;
		cin >> Query;
		//L ���� ��ĭ �̵�  (�Ǿ� ����)
		if (Query == 'L') {
			if (node[cursor].prev ==-1) continue;
			cursor = node[cursor].prev;
		}
		//D ������ ��ĭ �̵� (�ǵ� ����)
		else if (Query == 'D') {
			if (node[cursor].next == -1) continue;  //�ǵ�
			cursor = node[cursor].next;
		}
		//B (������ġ - 1) ��ġ ���� ���� (�Ǿ� ����) 
		else if (Query == 'B') {
			//****Ŀ�� �״�� -> ���Ḯ��Ʈ�� ����
			
			Node current = node[cursor];

			if (current.prev == -1) continue;

			Node remove = node[current.prev];

			//���ʿ� �ϳ��� ����
			if (remove.prev == -1) {
				node[cursor].prev = -1;
				node[current.prev].next = -2;
				node[current.prev].prev = -2;
			}
			//���ʿ� ������ ����
			else {
				node[cursor].prev = remove.prev;
				node[node[current.prev].prev].next = remove.next;

				//�����Ǵ� ����� ���� �����ֱ�
				node[current.prev].next = -2;
				node[current.prev].prev = -2;
			}	
		}
		// P $ : $���� ���ʿ� �߰�
		else if (Query == 'P') {
			char add; //�߰��� ����
			cin >> add;

			//���� cursor�� ���� ������ ��
			if (node[cursor].prev == -1) {
				node.push_back({ add,-1,cursor });
				node[cursor].prev = node.size() - 1;
			}
			//���� cursor�� ���� �������� ��
			else if (node[cursor].next == -1) {
				node.push_back({ add,node[cursor].prev ,cursor });
				node[node[cursor].prev].next = node.size() - 1;
				node[cursor].prev = node.size() - 1;
			}
			//���� cursor�� �߰��� ��
			else {
				node.push_back({ add,node[cursor].prev, node[node[cursor].prev].next });
				node[node[cursor].prev].next = node.size() - 1;
				node[cursor].prev = node.size() - 1;
			}
		}
	}
	int start = 0;

	for (int i = 0; i < node.size(); i++) {
		if (node[i].prev == -1) {
			start = i;
			break;
		}
	}


	while (node[start].next != -1) {
		cout << node[start].data;
		start = node[start].next;
	}

	int debugging = -1;


	return 0;
}


//�����м�
//�ð�: 0.3��  -> 3000����

//����ҹ���, �ִ� 60������

//L+1���� Ŀ�� (iterator����)


//��ɾ�
//L ���� ��ĭ �̵�  (�Ǿ� ����)
//D ������ ��ĭ �̵� (�ǵ� ����)
//B (������ġ - 1) ��ġ ���� ���� (�Ǿ� ����) 

//****Ŀ�� �״�� -> ���Ḯ��Ʈ�� ����

// P $ : $���� ���ʿ� �߰�


//��ɾ� ���� �� �ʱ� -> end()

