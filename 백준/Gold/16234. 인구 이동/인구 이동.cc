#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int N, L, R;
int Map[50][50] = { 0, };
const int dc[4] = { 0,0,-1,1 };
const int dr[4] = { -1,1,0,0 };
bool Visited[50][50] = { false, };
vector<pair<int, int>> Union;
int sum = 0;

void BFS(pair<int,int> start)
{
	queue<pair<int, int>> q;
	q.push(start);
	Visited[start.first][start.second] = true;

	while (!q.empty())
	{
		//cout << q.front().first << ", " << q.front().second<<"\n"; //Debugging
		pair<int, int> temp = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int next_r = temp.first + dr[dir];
			int next_c = temp.second + dc[dir];

			if (next_r < 0 || next_r >= N || next_c < 0 || next_c >= N||Visited[next_r][next_c]) continue;
			if ((abs(Map[next_r][next_c] - Map[temp.first][temp.second]) >= L)&& (abs(Map[next_r][next_c] - Map[temp.first][temp.second]) <= R))
			{
				q.push(make_pair(next_r, next_c));
				Visited[next_r][next_c] = true;

				Union.push_back(make_pair(next_r, next_c));
				sum += Map[next_r][next_c];
			}
		}		
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> L >> R;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cin >> Map[r][c];
		}
	}
	int day = 0;
	bool isUnion = true;
	while (isUnion)
	{
		isUnion = false;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				if (Visited[r][c] == false)
				{
					Union.clear();
					Union.push_back(make_pair(r, c));
					sum = Map[r][c];
					BFS(make_pair(r, c));

				}
				else continue;

				if (Union.size() >= 2)
				{
					isUnion = true;
					int pop_change = sum / Union.size();
					for (int i = 0; i < Union.size(); i++)
					{
						Map[Union[i].first][Union[i].second] = pop_change;
					}
				}
			}
		}
		if (isUnion) day++;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Visited[i][j] = false;
			}
		}
	}
	cout << day << "\n";
	return 0;
}