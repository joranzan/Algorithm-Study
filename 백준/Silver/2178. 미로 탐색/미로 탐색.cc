#include<iostream>
#include<vector>
#include<queue>
#include<string>

using namespace std;

//상하좌우
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
static int Map[101][101] = { 0, };
static bool Visited[101][101] = { false, };
static int N, M;

void BFS(int start_r, int start_c);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M;
	for (int r = 1; r <= N; r++)
	{
		string s;
		cin >> s;
		for (int c = 1; c <= M; c++)
		{
			Map[r][c] = s[c - 1] - '0';
		}
	}

	BFS(1, 1);

	return 0;
}

void BFS(int start_r, int start_c)
{
	queue<pair<int, int>> myQueue;
	myQueue.push(make_pair(start_r, start_c));
	Visited[start_r][start_c] = true;

	while (!myQueue.empty())
	{
		int current_r = myQueue.front().first;
		int current_c = myQueue.front().second;
		myQueue.pop();
		if (current_r == N && current_c == M)
		{
			cout << Map[current_r][current_c] << "\n";
			break;
		}
		for (int dir = 0; dir < 4; dir++)
		{
			int next_r = current_r + dr[dir];
			int next_c = current_c + dc[dir];
			if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > M || Map[next_r][next_c] == 0 || Visited[next_r][next_c]) continue;
			Visited[next_r][next_c] = true;
			Map[next_r][next_c] = Map[current_r][current_c] + 1;
			myQueue.push(make_pair(next_r, next_c));
		}
	}
}