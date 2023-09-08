#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	vector<int> Num;
	vector<int> Sum;

	Num.push_back(0);
	Sum.push_back(0);

	for (int index = 1; index <= N; index++)
	{
		int temp;
		cin >> temp;
		Num.push_back(temp);
		Sum.push_back(Sum[index - 1] + Num[index]);
	}

	for (int index = 1; index <= M; index++)
	{
		int i, j;
		cin >> i >> j;
		cout << Sum[j] - Sum[i - 1] << "\n";
	}

	return 0;
}