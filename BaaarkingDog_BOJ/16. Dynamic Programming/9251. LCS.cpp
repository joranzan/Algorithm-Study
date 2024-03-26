#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

//LCS(Longest Common Subsequence, ���� ���� �κ� ����)
//�� ������ �־����� ��, ����� �κ� ������ �Ǵ� ���� �� ���� �� ��

//1.�ش� ĭ�� ��� ���� ���ڰ� ���� ���� �ش� ĭ�� ���� �밢���� ���� + 1,

//2.�ش� ĭ�� ��� ���� ���ڰ� �ٸ� ���� �ش� ĭ�� ����, ���� �� �� ū ���� �����´�.


int DP[1001][1001] = { 0, };


int main() {
	ios::sync_with_stdio(false); 
	cin.tie(NULL); cout.tie(NULL);

	string s1;
	string s2;

	cin >> s1 >> s2;
	int len1 = s1.length();
	int len2 = s2.length();
	//0��° ��, 0��° ���� Dummy ������
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