#include<iostream>
#include<queue>

using namespace std;

int N, M;
int Map[8][8] = {0,};
const int dx[4] = { 0, 0, -1, +1 };
const int dy[4] = { -1, +1, 0, 0 };
int answer = 0;


void Infection()
{
	queue<int> q;
	int temp[8][8] = {0,};
	bool Visited[8][8] = { false, };

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			temp[y][x] = Map[y][x];
			if (temp[y][x] == 2)
			{
				q.push(10 * y + x);
				Visited[y][x] = true;
			}
		}
	}
	while (!q.empty())
	{
		int current_x = q.front() % 10;
		int current_y = q.front() / 10;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int next_x = current_x + dx[dir];
			int next_y = current_y + dy[dir];

			if (next_x >= M || next_x < 0 || next_y >= N || next_y < 0)
			{
				continue;
			}
			if (!Visited[next_y][next_x]&&temp[next_y][next_x] == 0)
			{
				temp[next_y][next_x] = 2;
				q.push(10 * next_y + next_x);
				Visited[next_y][next_x] = true;
			}
		}
	}
	int zero_num = 0;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			if (temp[y][x] == 0)
			{
				zero_num++;
			}
		}
	}
	if (answer < zero_num)
	{
		answer = zero_num;
	}
}



void Pick(int count, int start_x, int start_y)
{
	if (count == 3)
	{
		Infection();
		//감염&안전지대 구하는 함수
		return;
	}
	for (int y = start_y; y < N; y++)
	{
		for (int x = start_x; x < M; x++)
		{
			if (Map[y][x] == 0)
			{
				Map[y][x] = 1;
				Pick(count + 1, x, y);
				Map[y][x] = 0;
			}
		}
		start_x = 0;
	}
}

int main(void)
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}

	Pick(0, 0, 0);
	cout << answer;

	return 0;
}