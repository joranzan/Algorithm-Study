#include<iostream>

using namespace std;

//문제 분석
/*
오늘부터 N+1 날 퇴사
N일동안 최대한 많은 상담

//N+1 넘어가면 안됨

*/
int N;
int Arr[2][16] = { 0, }; //0인덱스 :T(기간) , 1인덱스 : P(금액)
int DP[16] = { 0, };  //했을 때 안했을 때



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