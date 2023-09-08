#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>

using namespace std;

typedef pair<int, int> pos;
int N, M;
int Answer = INT_MAX;
static vector<pos> House; 
static vector<pos> Chicken;
static vector<pos> Combi;
static bool Select[13] = { false };

void Combination(int index, int select_num);
int Distance();

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> M;
	
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			int temp;
			cin >> temp;
			if (temp == 1)
			{
				House.push_back(make_pair(i, j));
			}
			else if (temp == 2)
			{
				Chicken.push_back(make_pair(i, j));
			}
		}
	}
	Combination(0, 0);
	cout << Answer << "\n";

	return 0;
}
void Combination(int index, int select_num)
{
	if (select_num==M)
	{
		//치킨 거리 계산 함수 호출
		Answer = min(Answer, Distance());
		return;
	}
	for (int i = index; i < Chicken.size(); i++)
	{
		if (Select[i]) continue;
		Select[i] = true;
		Combi.push_back(Chicken[i]);
		Combination(i + 1, select_num + 1);
		Select[i] = false;
		Combi.pop_back();
	}
}
int Distance()
{
	int sum_distance = 0;
	
	for (auto &i : House)
	{
		int min_distance = INT_MAX;

		for (auto& j : Combi)
		{
			int chicken_r = j.first;
			int chicken_c = j.second;
			int house_r = i.first;
			int house_c = i.second;
			min_distance = min(min_distance, abs(chicken_r - house_r) + abs(chicken_c - house_c));
		}
		sum_distance += min_distance;
	}
	return sum_distance;
}