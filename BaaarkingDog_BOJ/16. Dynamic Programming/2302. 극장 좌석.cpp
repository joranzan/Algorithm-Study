#include<iostream>

using namespace std;

int N, M;
int Fixed[41] = { 0, };
int DP[41] = { 0, };


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int temp;
		cin >> temp;
		Fixed[temp] = 1;
	}

	DP[0] = 1;
	DP[1] = 1;


	for (int i = 2; i <= N; i++) {
		if (Fixed[i] == 1) DP[i] = DP[i - 1];
		else if (Fixed[i - 1] == 1) DP[i] = DP[i - 1];
		else {
			DP[i] = DP[i - 1] + DP[i - 2];
		}
	}

	cout << DP[N];

	return 0;
}

/*
�ڱ� ���� + ���� ������ ���� �� ����

VIP : ���¼� ����������

������� �¼��� �ش� ������

//N : 40��
//������ M ��

1 2 3 4 5 6 7 8 9 


�ȹٲ� 



4 5 
5 4 





*/