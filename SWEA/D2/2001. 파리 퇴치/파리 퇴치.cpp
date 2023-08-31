#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;



int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++)
	{

		int N, M;
		cin >> N >> M;

		int Map[15][15] = { 0, };
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> Map[i][j];
			}
		}
		int max = 0;
		for (int i = 0; i < N - (M - 1); i++)
		{
			for (int j = 0; j < N - (M - 1); j++)
			{
				int sum = 0;
				for (int r = i; r < i + M; r++)
				{
					for (int c = j; c < j + M; c++)
					{
						sum += Map[r][c];
					}
				}
				if (max < sum) max = sum;
			}
		}
		cout << "#"<<test<<" " << max << "\n";

	}


	return 0;
}