#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	vector<int> Num(10001, 0);
	int a = 0;

	for (int i = 1; i <= N; i++)
	{
		cin >> a;
		Num[a]++;
	}

	for (int i = 1; i <= 10000; i++)
	{
		if (Num[i] == 0) continue;
		for (int j = 1; j <= Num[i]; j++)
		{
			cout << i << "\n";
		}
	}
	return 0;
}