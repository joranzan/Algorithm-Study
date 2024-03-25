#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//LCS(Longest Common Subsequence, 최장 공통 부분 수열)
//두 수열이 주어졌을 때, 모두의 부분 수열이 되는 수열 중 가장 긴 것

//1.해당 칸의 행과 열의 문자가 같을 때는 해당 칸의 왼쪽 대각선의 값에 + 1,

//2.해당 칸의 행과 열의 문자가 다를 때는 해당 칸의 왼쪽, 위의 값 중 큰 값을 가져온다.


int DP[1001][1001] = { 0, };


int main() {
	ios::sync_with_stdio(false); 
	cin.tie(NULL); cout.tie(NULL);

	string s1;
	string s2;

	cin >> s1 >> s2;
	int len1 = s1.length();
	int len2 = s2.length();
	//0번째 행, 0번째 열은 Dummy 데이터
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (s1[i-1] == s2[j-1]) DP[i][j] = DP[i - 1][j - 1] + 1;
			else DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
		}
	}

	cout << DP[len1][len2];

	return 0;
}


/*
ex) ACAYKP  /  CAPCAK   -> ACAK
  C A P C A K
A 0 1 1 1 1 1 
C 1 1 1 2 2 2   
A 1 2 2 2 3 3
Y 1 2 2 2 3 3
K 1 2 2 2 3 4
P 1 2 3 3 3 4
*/