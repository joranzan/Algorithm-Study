#include<iostream>
#include<vector>

using namespace std;

int Map[50][50]={0,};
bool Visited[50][50] = { false, };
int N, M;
int Result;
//상 하 좌 우
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
void DFS(int start_r, int start_c);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++)
	{
		
		int K;
		cin >> M >> N >> K;

		if (test != 0)
		{
			for (int r = 0; r < N; r++)
			{
				for (int c = 0; c < M; c++)
				{
					Map[r][c] = 0;
					Visited[r][c] = false;
				}
			}
		}

		for (int i = 0; i < K; i++)
		{
			int r, c;
			cin >> c >> r;
			Map[r][c] = 1;
		}
		Result = 0;

		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < M; c++)
			{
				if (!Visited[r][c] && Map[r][c] == 1)
				{
					
					DFS(r, c);
					Result++;
				}
			}
		}
		cout << Result << "\n";
	}

	return 0;
}
void DFS(int start_r, int start_c)
{
	if (Visited[start_r][start_c] || Map[start_r][start_c]==0)
	{
		return;
	}

	Visited[start_r][start_c] = true;

	for (int dir = 0; dir < 4; dir++)
	{
		int current_r = start_r + dr[dir];
		int current_c = start_c + dc[dir];	
		if (current_r >= N || current_r < 0 || current_c >= M || current_c < 0 || Visited[current_r][current_c]) continue;
		if (Map[current_r][current_c] == 0) 
			continue;
		DFS(current_r, current_c);		
	}	
}