#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int Board[101][101] = { 0, };
bool Visited[101][101] = { false, };
vector<int> Result;

void BFS(int water_height,int row, int column);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int max_height = 0;
	cin >> N;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cin >> Board[r][c];
			if (max_height < Board[r][c])
			{
				max_height = Board[r][c];
			}
		}
	}
	if (max_height == 1)
	{
		cout << "1\n";
		return 0;
	}
	for (int h = 1; h < max_height; h++)
	{
		memset(Visited, false, sizeof(Visited));
		int count = 0;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < N; c++)
			{
				if (Board[r][c] > h && Visited[r][c] == false)
				{
					BFS(h,r,c);
					count++;
				}
			}
		}		
		Result.push_back(count);
	}

	int answer = 0;
	for (int i = 0; i < Result.size(); i++)
	{
		if (Result[i] > answer)
		{
			answer = Result[i];
		}
	}
	
	cout << answer << "\n";

	return 0;
}
void BFS(int water_height, int row, int column)
{
	if (Visited[row][column]) return;
	int current_row = row;
	int current_col = column;

	Visited[current_row][current_col] = true;

	for (int dir = 0; dir < 4; dir++)
	{
		int next_row = current_row + dr[dir];
		int next_col = current_col + dc[dir];
		if (next_row < 0 || next_col < 0 || next_row >= N || next_col >= N || Visited[next_row][next_col]) continue;
		if (Board[next_row][next_col] <= water_height) continue;
		BFS(water_height, next_row, next_col);
	}
}