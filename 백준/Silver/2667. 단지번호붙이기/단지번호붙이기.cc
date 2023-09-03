#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int N;
int Map[25][25] = { -1 };
bool Visited[25][25] = { false, };
vector<int> Result_arr;
int house_num = 0;
//상하좌우
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
void DFS(int start_r, int start_c);

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int r = 0; r < N; r++)
	{
		string s;
		cin >> s;
		for (int c = 0; c < N; c++)
		{
			int temp = s[c] - '0';
			Map[r][c]=temp;
			if (temp == 0) Visited[r][c] = true;
		}
	}
	Result_arr.push_back(0);
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (!Visited[r][c]&&Map[r][c]==1)
			{
				DFS(r, c);
				Result_arr.push_back(house_num);
				house_num = 0;
			}
		}
	}
	cout << Result_arr.size() - 1 << "\n";
	sort(Result_arr.begin() + 1, Result_arr.end());
	for (int i = 1; i < Result_arr.size(); i++)
	{
		cout << Result_arr[i] << "\n";
	}

	
	return 0;
}

void DFS(int start_r, int start_c)
{
	if (Visited[start_r][start_c] || Map[start_r][start_c] == 0)
	{
		
		return;
	}

	Visited[start_r][start_c] = true;
	house_num++;

	for (int dir = 0; dir < 4; dir++)
	{
		int current_r = start_r + dr[dir];
		int current_c = start_c + dc[dir];
		if (current_r >= N || current_r < 0 || current_c >= N || current_c < 0 || Map[current_r][current_c] == 0) continue;	
		if (Visited[current_r][current_c]) continue;
		DFS(current_r, current_c);
	}
}