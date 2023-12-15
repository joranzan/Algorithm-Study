#include<iostream>

using namespace std;

//��ģ���� ����
//1. 0���� �������� �ʴ´�
//2. 1�� �ι� �������� ��Ÿ���� �ʴ´�

//DP Table 2����?
// 
//��ǥ)
//N�ڸ� ��ģ�� ����

long long DP[2][91] = { 0, };
//0�� �ε��� -> �� ���ڰ� 0
//1�� �ε��� -> �� ���ڰ� 1

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	DP[0][1] = 0;
	DP[1][1] = 1;

	for (int i = 2; i <= N; i++) {
		DP[0][i] = DP[0][i - 1] + DP[1][i - 1];
		DP[1][i] = DP[0][i - 1];
	}

	cout << DP[0][N] + DP[1][N];

	return 0;
}