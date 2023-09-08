#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N;
int answer = 0;
int Map[17][17];
int dr[3] = { 0,1,1 }; //가로 세로 대각선
int dc[3] = { 1,0,1 }; //가로 세로 대각선

//모든 방향에서 행 r, 열 c가 1보다 작거나 N보다 크면 False, Map의 값이 1(벽)이면 False
//대각선 방향에서는 이웃하는 칸들도 1(벽)이면 false
bool Check(int r, int c)
{
	if ((r < 1) || (r > N) || (c < 1) || (c > N) || (Map[r][c] == 1))
	{
		return false;
	}
	else return true;
}
void DFS(pair<int, int> pos, int current_dir)
{
	if ((pos.first == N) && (pos.second == N))
	{
		answer++;
		return;
	}
	//아래의 경우들은 Check함수가 True를 반환할 때만 가능, False이면 contiue
	//current_dir이 0(가로방향) 일 때는 dir가 0, 2만 가능
	//current_dir이 1(세로방향) 일 때는 dir가 1, 2만 가능
	//current_dir이 2(대각선방향) 일 때는 dir가 0,1,2 모두 가능

	for (int dir = 0; dir < 3; dir++)
	{
			
		if (((current_dir == 0) && (dir == 1)) || ((current_dir == 1) && (dir == 0)))
		{
			continue;
		}
		//cout << dir << ": dir \n";

		int next_r = pos.first + dr[dir];
		int next_c = pos.second + dc[dir];

		if (!Check(next_r, next_c)) continue;

		if (((dir == 2) && (Map[next_r - 1][next_c] == 1)) || ((dir==2)&&(Map[next_r][next_c-1] == 1)))
		{
			continue; //대각선 이웃하는 칸들 안됨
		}
		pair<int, int> next_pos = make_pair(next_r, next_c);
		
		DFS(next_pos,dir);
		//cout << pos.first << " " << pos.second << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N;
	for (int r_idx = 1; r_idx <= N; r_idx++)
	{
		for (int c_idx = 1; c_idx <= N; c_idx++)
		{
			cin >> Map[r_idx][c_idx];
		}
	}
	
	DFS({ 1,2 }, 0);
	cout << answer << "\n";

	return 0;
}