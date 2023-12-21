#include<iostream>

using namespace std;

//���� �м�
/*
���ú��� N+1 �� ���
N�ϵ��� �ִ��� ���� ���

//N+1 �Ѿ�� �ȵ�

*/
int N;
int Arr[2][16] = { 0, }; //0�ε��� :T(�Ⱓ) , 1�ε��� : P(�ݾ�)
int DP[16] = { 0, };  //���� �� ������ ��



int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Arr[0][i] >> Arr[1][i];
	}

	for (int i = 1; i <= N; i++) {
		DP[i + 1] = max(DP[i], DP[i + 1]);
		if (i + Arr[0][i] > N + 1) continue;
		DP[i + Arr[0][i]] = max(DP[i + Arr[0][i]], DP[i] + Arr[1][i]);
	}

	cout << DP[N + 1];

	return 0;
}

/*
1   2    3   4    5    6    7
0   0    0  10    10   30   45
0   0    0  10    30   30


*/