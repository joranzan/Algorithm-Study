#include<iostream>
#include<algorithm>

using namespace std;

int N;
int Number[100] = { 0, };
int Operator[4] = { 0, };
int OperatorCnt = 0;
int OperatorArr[101] = { 0, };
int minAnswer = 2112345678;
int maxAnswer = -2112345678;

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> Number[i];
	for (int i = 0; i < 4; i++) {
		cin >> Operator[i];
		for (int j = OperatorCnt; j < OperatorCnt + Operator[i]; j++) {
			OperatorArr[j] = i;
		}
		OperatorCnt += Operator[i];
		
	}
}


void solution() {

	//Recursion(0, 0);
	do {
		int result = Number[0];
		for (int i = 0; i < OperatorCnt; i++) {
			if (OperatorArr[i] == 0) {  //����
				result += Number[i + 1];
			}
			else if (OperatorArr[i] == 1) {  //����
				result -= Number[i + 1];
			}
			else if (OperatorArr[i] == 2) {  //����
				result *= Number[i + 1];
			}
			else if (OperatorArr[i] == 3) {  //������
				if (result == 0) continue;
				else if (result < 0) {
					result = abs(result) / Number[i + 1];
					result *= -1;
				}
				else if (result > 0) {
					result /= Number[i + 1];
				}
			}
		}
		minAnswer = min(minAnswer, result);
		maxAnswer = max(maxAnswer, result);
	} while (next_permutation(OperatorArr, OperatorArr + OperatorCnt));

	cout << maxAnswer << "\n" << minAnswer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}

/*
N���� �� 
N-1���� ������

1) ������ ���� �ٲٸ� �ȵ� --> ������ ������ �ٲ� �� ����
2) �켱���� �����ϰ� ������� ������ ����
3) ������ ����� ���� �� C++14 ����
(����� �ٲ� �� ���� ���ϰ�, �� ���� ������ �ٲ� �Ͱ� ����)





*/