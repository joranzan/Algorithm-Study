#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, K;
	int answer = 0;
	cin >> N >> K;
	vector<int> Coin(N, 0);

	for (int i = 0; i < N; i++)
	{
		cin >> Coin[i];
	}

	for (int i = N - 1; i >= 0; i--)
	{
		if (K < Coin[i]) continue;
		answer = answer + (K / Coin[i]);
		K = K % Coin[i];
		if (K == 0) break;
	}

	cout << answer << "\n";

	return 0;
}