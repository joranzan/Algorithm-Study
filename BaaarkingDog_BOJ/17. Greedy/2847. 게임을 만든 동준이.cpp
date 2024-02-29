#include<iostream>

using namespace std;

int Score[101] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	int Answer = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Score[i];
	}

	for (int i = N - 2; i >= 0; i--) {
		
		if (Score[i] >= Score[i + 1]) {
			int decreased = Score[i] - (Score[i + 1] - 1);
			Score[i] = Score[i + 1] - 1;
			Answer += decreased;
		}

	}
	
	cout << Answer;

	return 0;
}

/*

���� ����

N���� Level
- �¶��� ���� (���� Ŭ���� �� �� ���� ������ �� ����)
- ������ ���̵� �� ��ġ (���� ȹ�� �ȸ���)


��ǥ : �� ������ Ŭ������ �� ��� ���� ���

- Ư�� ������ ���� ���ҽ�Ŵ


���� ����

- ���� > 0
- 1��ŭ ���� : 1��
- �ּ������� ���� ������

��� : �� �� ����?


*/


/*

������ ���ҽ�Ű�⸸ �ϹǷ� ������ ���� ���� ������ ��

���� ������ ������
1) ���� ������ �������� ������ ���� �ʿ� X
2) ���� ������ �������� ũ�ų� ������
(���� ������ ���� - 1)�� ����� ���� �����ؾ��ϴ� Ƚ�� ���
Answer�� �߰�

TC 1 

5 5 5

3 4 5


TC 2

5 3 7 5

2 3 4 5
-3	-3

*/