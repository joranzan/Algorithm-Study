//사이클 여부 탐색하는 문제
#include<iostream>
#include<vector>

using namespace std;
static int V, E;
static vector<vector<int>> AdjacentList;
static vector<bool> Visited;
static vector<int> Set_Info;
static bool isEven;

void DFS(int start);

int main()
{
	int T;
	cin >> T;
	for (int test = 0; test < T; test++)
	{
		cin >> V >> E;
		AdjacentList.resize(V + 1);
		Visited = vector<bool>(V + 1, false);
		Set_Info = vector<int>(V + 1, 0);
		isEven = true;

		for (int i = 0; i < E; i++)
		{
			int from, to;
			cin >> from >> to;
			AdjacentList[from].push_back(to);
			AdjacentList[to].push_back(from);
		}

		for (int i = 1; i <= V; i++)
		{
			
			if (isEven)
			{
				DFS(i);
			}
			if (!isEven)
			{
				cout << "NO\n";
				break;
			}
		}
		
		if (isEven)
		{
			cout << "YES\n";
		}
		AdjacentList.clear();
	}

	return 0;
}
void DFS(int start)
{
	
	Visited[start] = true;
	for (auto i : AdjacentList[start])
	{
		if (!Visited[i])
		{
			Set_Info[i] = (Set_Info[start] + 1) % 2;
			DFS(i);
		}
		else if (Set_Info[start]==Set_Info[i])
		{
			isEven = false;
			break;
		}
	}
}