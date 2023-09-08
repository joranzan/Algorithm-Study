#include<iostream>
#include<vector>

using namespace std;
const int dr[5] = { 0,0,0,-1,1 };
const int dc[5] = { 0,1,-1,0,0 };
//주사위 배열 -> 1:윗면 6:아랫면
vector<int> Roll(int direction, vector<int> dice);

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	vector<vector<int>> Map(N, vector<int>(M, 0));
	int start_x, start_y;
	cin >> start_x >> start_y;
	int K;
	cin >> K;
	vector<int> command(K);
	//맵의 칸에 해당하는 값 입력받기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}
	//명령 받기
	for (int i = 0; i < K; i++)
	{
		cin >> command[i];
	}

	int current_x = start_x;
	int current_y = start_y;
	vector<int> dice_array(7, 0);
	for (int i = 0; i < K; i++)
	{
		int direction = command[i];
		int next_x = current_x + dr[direction];
		int next_y = current_y + dc[direction];
		if (next_x < 0 || next_y < 0 || next_x >= N || next_y >= M) continue;
		if (Map[next_x][next_y] == 0)
		{
			dice_array = Roll(direction, dice_array);
			Map[next_x][next_y] = dice_array[6];
		}
		else
		{
			dice_array = Roll(direction, dice_array);
			dice_array[6] = Map[next_x][next_y];
			Map[next_x][next_y] = 0;
		}
		cout << dice_array[1] << "\n";
		current_x = next_x;
		current_y = next_y;
	}
	return 0;
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