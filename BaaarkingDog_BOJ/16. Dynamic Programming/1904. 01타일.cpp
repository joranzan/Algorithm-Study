#include<iostream>

using namespace std;

/*
타일 : 00, 1

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


현재자리: 0  -> 자동으로 +2칸뒤로 넘어가야함 (만약 2칸 뒤가 없다면 0 못놓음) 
현재자리: 1 -> 다음으로 이동



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