#include<iostream>

using namespace std;

int N;

void Recursion(int n) {

	if (n == 0) {
		for (int i = 0; i < N - n; i++) {
			cout << "____";
		}
		cout << "\"����Լ��� ������?\"\n";
		for (int i = 0; i < N - n; i++) {
			cout << "____";
		}
		cout << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n";
		for (int i = 0; i < N - n; i++) {
			cout << "____";
		}
		cout<<"��� �亯�Ͽ���.\n";
		return;
	}
	for (int i = 0; i < N - n; i++) {
		cout << "____";
	}
	cout << "\"����Լ��� ������?\"\n";
	for (int i = 0; i < N - n; i++) {
		cout << "____";
	}
	cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n";
	for (int i = 0; i < N - n; i++) {
		cout << "____";
	}
	cout<< "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n";
	for (int i = 0; i < N - n; i++) {
		cout << "____";
	}
	cout<<"���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n";
	Recursion(n - 1);
	for (int i = 0; i < N - n; i++) {
		cout << "____";
	}
	cout << "��� �亯�Ͽ���.\n";
}

int main() {

	cin >> N;
	
	cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n";
	Recursion(N);

	return 0;
}

//
// 4
// 4
// 4
// 4
// 8
// 8
// 8
// 4
//