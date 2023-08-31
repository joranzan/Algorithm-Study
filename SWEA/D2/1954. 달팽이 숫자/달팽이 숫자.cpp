#include<iostream>
#include<vector>

using namespace std;


//dir: 0: 우 1: 하: 2:좌 3:상

const int dy[4] = { 0,1,0,-1 };
const int dx[4] = { 1,0,-1,0 };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 0; test < T; test++)
	{		
		// input
		int N;
		cin >> N;
		
		int arr[10][10] = { 0, };

		int number = 1;
		int dir = 0;
		int y = 0, x = 0;

		while (number <= (N * N))
		{
			arr[y][x] = number;

			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (number >= N * N) break;
			if (ny >= N || nx >= N || ny < 0 || nx < 0 || arr[ny][nx] != 0)
			{
				dir++;
				dir = dir % 4;
			}
			y = y + dy[dir];
			x = x + dx[dir];
			number++;
		}
		cout << "#" << test + 1 << "\n";
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << "\n";
		}

	}

	return 0;
}