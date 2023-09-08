#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

static vector<vector<int>> Board;
static int N, K;
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

int Solve();
bool isFinished();
void RollDown();
void MoveFish();
void MinFishPlus();

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;
	Board = vector<vector<int>>(N, vector<int>(N, -1));
	for (int i = 0; i < N; i++)
	{
		cin >> Board[0][i];
	}

	
	cout << Solve() << "\n";

	return 0;
}

int Solve()
{
	int count = 0;
	while (!isFinished())
	{
		count++;
		MinFishPlus();
		RollDown();
	}
	return count;
}

bool isFinished()
{
	int max_value = *max_element(Board[0].begin(), Board[0].end());
	int min_value = *min_element(Board[0].begin(), Board[0].end());
	if (max_value - min_value <= K) return true;
	else return false;
}

void MinFishPlus()
{
	int min_fish = *min_element(Board[0].begin(), Board[0].end());
	for (int i = 0; i < N; i++)
	{
		if (Board[0][i] == min_fish)
		{
			Board[0][i]++;
		}
	}
}

void RollDown()
{
	int length_r = 1;
	int length_c = 1;
	int start_c = 0;

	while (length_r + length_c + start_c <= N)
	{
		for (int r = 0; r < length_r; r++)
		{
			for (int c = 0; c < length_c; c++)
			{
				//손으로 그리면서 이해해보기
				int next_r = length_c - c;
				int next_c = start_c + length_c + r;
				Board[next_r][next_c] = Board[r][c + start_c];
				Board[r][c + start_c] = -1;
			}
		}
		start_c += length_c;
		if (length_c == length_r) length_r++;
		else length_c++;
	}

	MoveFish();

	start_c = 0;
	length_r = 1;
	length_c = N / 2;


	for (int i = 0; i < 2; i++)
	{
		for (int r = 0; r < length_r; r++)
		{
			for (int c = 0; c < length_c; c++)
			{
				int next_r = 2 * length_r - r - 1;
				int next_c = 2 * length_c + start_c - c - 1;
				Board[next_r][next_c] = Board[r][c + start_c];
				Board[r][c + start_c] = -1;
			}
		}
		start_c += length_c;
		length_c /= 2;
		length_r *= 2;
	}
	
	MoveFish();
}

void MoveFish()
{
	vector<vector<int>> Board_temp = Board;
	
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (Board[r][c] == -1) continue;
			for (int dir = 0; dir < 4; dir++)
			{
				int next_r = r + dr[dir];
				int next_c = c + dc[dir];
				if (next_r < 0 || next_c < 0 || next_r >= N || next_c >= N) continue;
				if (Board[next_r][next_c] == -1) continue;				
				Board_temp[r][c] -= (int)(Board[r][c] - Board[next_r][next_c]) / 5;
			}
		}
	}
	vector<int> FlatBowl;
	for (int c = 0; c < N; c++)
	{
		for (int r = 0; r < N; r++)
		{
			if (Board_temp[r][c] == -1) continue;
			FlatBowl.push_back(Board_temp[r][c]);
		}
	}

	Board = vector<vector<int>>(N, vector<int>(N, -1));
	Board[0] = FlatBowl;
}