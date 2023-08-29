#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

static vector<vector<pair<int,int>>> AdjacentList; //정점< (정점, 가중치) >
static vector<bool> Visited;
static vector<int> Distance;

void BFS(int start);


int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int V;
	cin >> V;

	AdjacentList.resize(V + 1);
	Visited = vector<bool>(V + 1, false);
	Distance = vector<int>(V + 1, 0);

	for (int i = 1; i <= V; i++)
	{
		int u;
		cin >> u;
		while (1)
		{
			int v, w;
			cin >> v;
			if (v == -1) break;
			cin >> w;
			AdjacentList[u].push_back(make_pair(v, w));			
		}
	}
	BFS(1);
	int Max = 1;
	for (int i = 1; i <= V; i++)
	{
		if (Distance[i] > Distance[Max])
			Max = i;
	}

	fill(Distance.begin(), Distance.end(), 0);
	fill(Visited.begin(), Visited.end(), false);
	BFS(Max);
	sort(Distance.begin(), Distance.end());
	cout << Distance[V] << "\n";

	return 0;
}

void BFS(int start)
{
	queue<pair<int, int>> myQueue;
	myQueue.push(make_pair(start, 0));
	Visited[start] = true;

	while (!myQueue.empty())
	{
		int current_node = myQueue.front().first;
		int weight = myQueue.front().second;
		myQueue.pop();

		for (auto i : AdjacentList[current_node])
		{
			int next_node = i.first;
			int next_weight = i.second;
			if (Visited[next_node]) continue;
			myQueue.push(make_pair(next_node, next_weight));
			Distance[next_node] = Distance[current_node] + next_weight;
			Visited[next_node] = true;
		}
	}
}