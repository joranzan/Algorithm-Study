#include<iostream>

using namespace std;

/*
Ÿ�� : 00, 1

N=1
1

N=2

00
11

N=3
001
100
111

N=4

0000
0011
1001
1100
1111

N=5
00001
00100
10000
00111
10011
11001
11100
11111


�����ڸ�: 0  -> �ڵ����� +2ĭ�ڷ� �Ѿ���� (���� 2ĭ �ڰ� ���ٸ� 0 ������) 
�����ڸ�: 1 -> �������� �̵�



*/

int DP[1000001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i <= N; i++) {
		DP[i] = DP[i - 2] + DP[i - 1];
		if (DP[i] >= 15746) DP[i] %= 15746;
	}

	cout << DP[N];

	return 0;
}