#include<iostream>
#include<vector>
#include<queue>
#include<limits.h>

using namespace std;

typedef pair<int, int> edge;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int V, E;
	cin >> V >> E;
	vector<vector<edge>> AdjacentList(V + 1);
	vector<int> Shortest(V + 1, INT_MAX);
	vector<bool> Visited(V + 1, false);

	int K;
	cin >> K;
	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		AdjacentList[u].push_back(make_pair(v, w));
	}

	Shortest[K] = 0;

	//****************************************
	priority_queue<edge,vector<edge>,greater<edge>> myQueue;
	myQueue.push(make_pair(0, K));


	while (!myQueue.empty())
	{
		edge current = myQueue.top();
		myQueue.pop();
		int current_v = current.second;
		if (Visited[current_v]) continue;
		Visited[current_v] = true;
		for (int i = 0; i<AdjacentList[current_v].size(); i++)
		{
			int next_node = AdjacentList[current_v][i].first;
			int next_value = AdjacentList[current_v][i].second;
			if (Shortest[next_node] > Shortest[current_v] + next_value)
			{
				Shortest[next_node] = Shortest[current_v] + next_value;
				myQueue.push(make_pair(Shortest[next_node], next_node));
			}
			
		}
	}
	for (int i = 1; i < Shortest.size(); i++)
	{
		if (Shortest[i] == INT_MAX)
		{
			cout << "INF\n";
		}
		else
		{
			cout << Shortest[i] << "\n";
		}

	}

}