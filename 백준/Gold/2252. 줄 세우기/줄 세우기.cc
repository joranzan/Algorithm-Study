#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;

	vector<vector<int>> AdjacentList(N + 1);
	vector<int> InDegree(N + 1, 0);
	vector<int> result;

	for (int i = 0; i < M; i++)
	{
		int A, B;
		cin >> A >> B;
		AdjacentList[A].push_back(B);
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < AdjacentList[i].size(); j++)
		{
			InDegree[AdjacentList[i][j]]++;
		}
	}

	queue<int> sort;
	
	for (int i = 1; i <= N; i++)
	{
		if (InDegree[i] == 0)
		{
			sort.push(i);
		}
	}
	vector<bool> Visited(N + 1, false);
	while (!sort.empty())
	{
		result.push_back(sort.front());
		int current = sort.front();
		Visited[current] = true;
		sort.pop();

		for (auto i : AdjacentList[current])
		{
			if (Visited[i] == true) continue;
			InDegree[i]--;
			if (InDegree[i] != 0) continue;
			sort.push(i);
			
		}
	}

	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << " ";
	}

	return 0;
}