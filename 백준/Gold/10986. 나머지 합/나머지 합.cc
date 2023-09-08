#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int N, M;
	cin >> N >> M;
	
	vector<long> Sum(N, 0);
	vector<long> Remainder(M, 0);
	long Answer = 0;

	for (int i = 0; i < N; i++)
	{
		if (i == 0)
		{
			cin >> Sum[0];
			continue;
		}
		long temp;
		cin >> temp;
		Sum[i] = Sum[i - 1] + temp;
	}
	for (int i = 0; i < N; i++)
	{
		Sum[i] = Sum[i] % M;
		if (Sum[i] == 0) Answer++;
		Remainder[Sum[i]]++;
	}
	for (int i = 0; i < M; i++)
	{
		if (Remainder[i] >= 2)
		{
			Answer += (Remainder[i] * (Remainder[i] - 1)) / 2;
		}
	}
	cout << Answer << "\n";
	return 0;
}