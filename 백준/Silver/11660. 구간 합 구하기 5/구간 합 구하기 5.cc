#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	vector<vector<int>> Num(N + 1, vector<int>(N + 1, 0));
	vector<vector<int>> Sum(N + 1, vector<int>(N + 1, 0));

	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			cin >> Num[row][col];
			Sum[row][col] = Sum[row - 1][col] + Sum[row][col - 1] - Sum[row - 1][col - 1] + Num[row][col];
		}
	}

	for (int tc = 1; tc <= M; tc++)
	{
		int X1, Y1, X2, Y2;
		cin >> X1 >> Y1 >> X2 >> Y2;
		int sum = Sum[X2][Y2] - (Sum[X2][Y1 - 1] + Sum[X1 - 1][Y2] - Sum[X1 - 1][Y1 - 1]);
		cout << sum << "\n";
	}
	return 0;
}