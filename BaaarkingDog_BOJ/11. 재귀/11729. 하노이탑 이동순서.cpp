#include<iostream>

using namespace std;

//��ǥ: 3��° ���� �ű��

//���� �м�
//3���� ���
//N���� �ݰ� �ٸ� ���� (N 20����)

int Hanoi[3][21] = { 0 ,};   //0:���� 1:����
int N;

void input() {

	cin >> N;
	for (int i = 1; i <= N; i++) {
		Hanoi[1][i] = 1;
	}

}

void DFS() {
	


	
}

void solution() {

}

int main() {

	input();
	solution();

	return 0;
}