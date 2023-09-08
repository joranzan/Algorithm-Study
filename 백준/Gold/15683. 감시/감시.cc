#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N, M;
int Office[8][8];
int Min = 64;
//상:0 우:1 하:2 좌:3
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

struct CCTV_Pos
{
	int num;
	pair<int, int> point;
	bool operator<(const CCTV_Pos& other) const
	{
		return num < other.num;
	}
};

priority_queue<CCTV_Pos> CCTV_Info;
void CCTV_selection(int y, int x, int n, int dir);
void CCTV_Move(int current_y, int current_x, int dir);
void DFS();



void CCTV_selection(int y, int x, int n, int dir)
{
	switch (n) {
	case 1: {
		CCTV_Move(y, x, dir);
		break;
	}
	case 2: {
		CCTV_Move(y, x, dir);
		CCTV_Move(y, x, dir + 2);
		break;
	}
	case 3: {
		CCTV_Move(y, x, dir);
		CCTV_Move(y, x, dir + 1);
		break;
	}
	case 4: {
		CCTV_Move(y, x, dir);
		CCTV_Move(y, x, dir + 1);
		CCTV_Move(y, x, dir + 2);
		break;
	}
	case 5: {
		CCTV_Move(y, x, dir);
		CCTV_Move(y, x, dir + 1);
		CCTV_Move(y, x, dir + 2);
		CCTV_Move(y, x, dir + 3);
		break;
	}
	}
}
void CCTV_Move(int current_y, int current_x, int dir)
{
	dir = dir % 4;
	while (true)
	{
		current_y += dy[dir];
		current_x += dx[dir];
		if (current_x < 0 || current_y < 0 || current_x >= M || current_y >= N) return;
		if (Office[current_y][current_x] == 6) return;
		if (Office[current_y][current_x] != 0) continue;
		Office[current_y][current_x] = 7;
	}
}

void DFS()
{
	//cout <<"DFS\n";
	if (CCTV_Info.empty())
	{
		int count = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				//cout << Office[i][j] << " ";
				if (Office[i][j] == 0)
					count++;
			}
			//cout << "\n";
		}
		if (Min > count) Min = count;
		return;
	}
	int BackUp[8][8];
	int current_y = CCTV_Info.top().point.first;
	int current_x = CCTV_Info.top().point.second;
	int CCTV_Num = CCTV_Info.top().num;
	for (int dir = 0; dir < 4; dir++)
	{
		priority_queue<CCTV_Pos> temppq;
		temppq = CCTV_Info;
		//Office 복사해놓기
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				BackUp[i][j] = Office[i][j];
			}
		}
		CCTV_selection(current_y, current_x, CCTV_Num, dir);
		CCTV_Info.pop();
		DFS();
		//Office 다시 백업
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				Office[i][j] = BackUp[i][j];
			}
		}
		//Priority Queue 백업
		CCTV_Info = temppq;
	}
}


int main()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < M; x++)
		{
			cin >> Office[y][x];
			if (Office[y][x] != 0 && Office[y][x] != 6)
			{
				CCTV_Pos pos;
				pos.num = Office[y][x];
				pos.point = (make_pair(y, x));
				CCTV_Info.push(pos);
				
			}
		}
	}
	DFS();
	cout << Min;
	return 0;
}
