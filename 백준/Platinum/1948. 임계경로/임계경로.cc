#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;

	vector<vector<pair<int,int>>> AdjacentList(N + 1);
	vector<vector<pair<int,int>>> ReverseList(N + 1);
	vector<int> Degree(N + 1, 0);
	vector<int> Time(N + 1, 0);
	vector<bool> Visited(N + 1, false);

	int start, destin;

	for (int i = 0; i < M; i++)
	{
		int A, B, t;
		cin >> A >> B >> t; 
		AdjacentList[A].push_back(make_pair(B, t));
		ReverseList[B].push_back(make_pair(A, t));
		Degree[B]++;
	}

	cin >> start >> destin;
	
	queue<int> myQueue;
	myQueue.push(start);
	
	while (!myQueue.empty())
	{
		int current = myQueue.front();
		Visited[current] = true;
		myQueue.pop();
		for (int i = 0; i < AdjacentList[current].size(); i++)
		{
			//if (Visited[AdjacentList[current][i].first]) continue;   //일방향 사이클 x 이므로 굳이 필요없음
			Degree[AdjacentList[current][i].first]--;
			Time[AdjacentList[current][i].first] = max(Time[current] + AdjacentList[current][i].second, Time[AdjacentList[current][i].first]);
			if (Degree[AdjacentList[current][i].first] == 0)
			{
				myQueue.push(AdjacentList[current][i].first);
			}
		}		
	}
	
	
	int noRest = 0;
	queue<int> myQQueue;
	myQQueue.push(destin);
	Visited = vector<bool>(N + 1, false);
    Visited[destin] = true;

	while (!myQQueue.empty())
	{
		int back = myQQueue.front();
		
		myQQueue.pop();
		for (pair<int, int> next : ReverseList[back])
		{
			if (next.second + Time[next.first] >= Time[back])
			{
				noRest++;
				if (Visited[next.first]) continue;
                Visited[next.first] = true;
				myQQueue.push(next.first);
			}
		}
	}
	cout << Time[destin] << "\n";
	cout << noRest << "\n";
	return 0;
}