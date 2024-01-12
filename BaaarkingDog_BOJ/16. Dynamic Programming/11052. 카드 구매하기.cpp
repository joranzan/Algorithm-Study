#include<iostream>

using namespace std;

int N;
int Cost[1001] = { 0, };
int DP[1001] = { 0, };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> Cost[i];
		DP[i] = Cost[i];
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i + j > N) break;
			DP[i + j] = max(DP[i + j], DP[i] + Cost[j]);
		}
	}

	cout << DP[N];

	return 0;
}

/*
���� �м�

1) ī�� 1~N���� ���Ե� ī����

2) ���� �ִ��� ���� �����ؼ� ī�� N�� ����


*/