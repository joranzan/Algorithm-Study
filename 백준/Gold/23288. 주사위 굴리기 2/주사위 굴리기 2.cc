#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
static vector<vector<int>> ScoreMap;
static vector<vector<int>> Map;
static vector<vector<bool>> Visited;
const int dr[5] = { 0,0,0,-1,1 };
const int dc[5] = { 0,1,-1,0,0 };

int ChangeOpposite(int direction);
int RotateClock(int direction);
int RotateClockWise(int direction);
void BFS(int current_r,int current_y);
const int dr_dice[5] = { 0,0,0,-1,1 };
const int dc_dice[5] = { 0,1,-1,0,0 };
//주사위 배열 -> 1:윗면 6:아랫면
vector<int> Roll(int direction, vector<int> dice);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	ScoreMap = vector<vector<int>>(N + 1, vector<int>(M + 1, 0));
	Map = vector<vector<int>>(N + 1, vector<int>(M + 1, 0));
	Visited = vector<vector<bool>>(N + 1, vector<bool>(M + 1, false));
	int K;
	cin >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> Map[i][j];
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (Visited[i][j] == false)
			{
				BFS(i, j);
				Visited[i][j] = true;
			}
		}
	}

	vector<int> dicearr(7);
	for (int i = 1; i < 7; i++)
	{
		dicearr[i] = i;
	}
	int answer = 0;
	int dir = 1;
	int current_r = 1, current_c = 1;
	for (int i = 0; i < K; i++)
	{
		int next_r = current_r + dr[dir];
		int next_c = current_c + dc[dir];
		if (next_r<1 || next_c<1 || next_r>N || next_c>M)
		{
			dir = ChangeOpposite(dir);
			next_r = current_r + dr[dir];
			next_c = current_c + dc[dir];
		}
		answer += ScoreMap[next_r][next_c];
		dicearr = Roll(dir, dicearr);
		int a = dicearr[6];
		int b = Map[next_r][next_c];
		if (a > b)
		{
			dir = RotateClock(dir);
		}
		else if (a < b)
		{
			dir = RotateClockWise(dir);
		}
		current_r = next_r;
		current_c = next_c;
	}
	cout << answer << "\n";

	return 0;
}

void BFS(int r,int c)
{
	queue<pair<int, int>> result;
	queue<pair<int, int>> myQueue;
	int num = Map[r][c];
	myQueue.push(make_pair(r, c));
	Visited[r][c] = true;

	while (!myQueue.empty())
	{
		int current_r = myQueue.front().first;
		int current_c = myQueue.front().second;
		result.push(make_pair(current_r, current_c));
		myQueue.pop();

		for (int dir = 1; dir <= 4; dir++)
		{
			int next_r = current_r + dr[dir];
			int next_c = current_c + dc[dir];
			if (next_r<1 || next_c<1 || next_r>N || next_c>M) continue;
			if (Visited[next_r][next_c]) continue;
			if (Map[next_r][next_c] != num) continue;
			Visited[next_r][next_c] = true;
			myQueue.push(make_pair(next_r, next_c));
		}
	}
	int cnt = result.size();
	while (!result.empty())
	{
		ScoreMap[result.front().first][result.front().second] = num * cnt;
		result.pop();
	}
}
vector<int> Roll(int direction, vector<int> dice)
{
	switch (direction)
	{
	case 1:  //동
	{
		dice[0] = dice[4];
		dice[4] = dice[6];
		dice[6] = dice[3];
		dice[3] = dice[1];
		dice[1] = dice[0];
		break;
	}
	case 2:  //서
	{
		dice[0] = dice[3];
		dice[3] = dice[6];
		dice[6] = dice[4];
		dice[4] = dice[1];
		dice[1] = dice[0];
		break;
	}
	case 3:  //북
	{
		dice[0] = dice[5];
		dice[5] = dice[6];
		dice[6] = dice[2];
		dice[2] = dice[1];
		dice[1] = dice[0];
		break;
	}
	case 4:  //남
	{
		dice[0] = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[6];
		dice[6] = dice[5];
		dice[5] = dice[0];
		break;
	}
	}
	return dice;
}
int ChangeOpposite(int direction)
{
	switch (direction)
	{
	case 1:
	{
		direction = 2;
		break;
	}
	case 2:
	{
		direction = 1;
		break;
	}
	case 3:
	{
		direction = 4;
		break;
	}
	case 4:
	{
		direction = 3;
		break;
	}
	}
	return direction;
}
int RotateClock(int direction)
{
	switch (direction)
	{
	case 1:
	{
		direction = 4;
		break;
	}
	case 2:
	{
		direction = 3;
		break;
	}
	case 3:
	{
		direction = 1;
		break;
	}
	case 4:
	{
		direction = 2;
		break;
	}
	}
	return direction;
}
int RotateClockWise(int direction)
{
	switch (direction)
	{
	case 1:
	{
		direction = 3;
		break;
	}
	case 2:
	{
		direction = 4;
		break;
	}
	case 3:
	{
		direction = 2;
		break;
	}
	case 4:
	{
		direction = 1;
		break;
	}
	}
	return direction;
}
