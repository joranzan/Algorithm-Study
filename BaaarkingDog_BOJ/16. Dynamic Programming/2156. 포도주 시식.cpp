#include<iostream>

using namespace std;

int N;
int DP[10001] = { 0, };
int Wine[10001] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Wine[i];
	}

	DP[1] = Wine[1];
	DP[2] = DP[1] + Wine[2];


	for (int i = 3; i <= N; i++) {
		
		int a = DP[i - 2] + Wine[i];
		int b = DP[i - 3] + Wine[i - 1] + Wine[i];
		int c = DP[i - 1];

		DP[i] = max(a, max(b, c));
	}


	cout << DP[N];

	return 0;
}

//���ð� ���� ��ġ
//���� 3�� �ȵ�

/*
���ðų� �ȸ��ðų�

OOX
OXX -> �� �� �ʿ����
XOX -> ���� �ʿ����
XXX  -> �� �� �ʿ����

XXO  -> �� �� �ʿ����
XOO
OXO


DP[i] = DP[i-3] + Wine[i-1] + Wine[i]
DP[i] = DP[i-2] + Wine[i]


*/
