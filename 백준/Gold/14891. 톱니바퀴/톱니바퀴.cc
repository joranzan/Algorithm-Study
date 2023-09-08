#include<iostream>
#include<vector>
#include<string>

using namespace std;
static vector<vector<int>> Wheel;

void rotation(int w, int dir)
{
	if (dir == 1)   // 시계방향
	{
		int temp = Wheel[w][7];
		for (int i = 7; i > 0; i--)
		{
			Wheel[w][i] = Wheel[w][i - 1];
		}
		Wheel[w][0] = temp;
	}
	else
	{
		int temp = Wheel[w][0];
		for (int i = 1; i < 8; i++)
		{
			Wheel[w][i - 1] = Wheel[w][i];
		}
		Wheel[w][7] = temp;
	}
}


void Simulation(int w, int dir)
{
	int left_compare = Wheel[w][6];
	int right_compare = Wheel[w][2];
	rotation(w, dir);
	//3 -1
	int left_dir = dir;
	for (int i = w - 1; i > 0; i--)     // i:2 dir:-1 
	{
		if (left_compare == Wheel[i][2]) break;
		else
		{
			if (left_dir == 1)
			{
				left_compare = Wheel[i][6];
				rotation(i, -1);
				left_dir = -1;
			}
			else
			{
				left_compare = Wheel[i][6];
				rotation(i, 1);
				left_dir = 1;
			}
		}
	}
	int right_dir = dir;
	for (int i = w + 1; i < 5; i++)   // i:4 dir:-1
	{
		if (right_compare == Wheel[i][6]) break;
		else
		{
			if (right_dir == 1)
			{
				right_compare = Wheel[i][2];
				rotation(i, -1);
				right_dir = -1;
			}
			else
			{
				right_compare = Wheel[i][2];
				rotation(i, 1);
				right_dir = 1;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Wheel = vector<vector<int>>(5, vector<int>(8, -1));
	string info;
	for (int i = 1; i <= 4; i++)
	{
		cin >> info;
		for (int j = 0; j < 8; j++)
		{
			int info_int = info[j] - '0';
			Wheel[i][j] = info_int;
		}
	}

	int K;
	cin >> K;
	for (int i = 0; i < K; i++)
	{
		int rotate_wheel;
		int dir;     //  시계방향:1    반시계방향: -1
		cin >> rotate_wheel >> dir;
		Simulation(rotate_wheel, dir);
	}

	int result = (Wheel[1][0] * 1) + (Wheel[2][0] * 2) + (Wheel[3][0] * 4) + (Wheel[4][0] * 8);
	cout << result << "\n";

	return 0;
}