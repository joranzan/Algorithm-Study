#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int N, M;
vector<int> num;
map<int, bool> Visited;
vector<int> Result;

void DFS(int cnt)
{
	if (cnt == M)
	{
		for (int i = 0; i < M; i++)
		{
			cout << Result[i] << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = 0; i < N; i++)
	{
		if (!Visited.at(num[i]))
		{
			Visited.at(num[i]) = true;
			Result[cnt] = num[i];
			DFS(cnt + 1);
			Visited.at(num[i]) = false;
		}
	}	
}

int main()
{
	
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> N >> M;

	
	num.resize(N);
	Result.resize(M);
	for (int i = 0; i < N; i++)
	{
		cin >> num[i];
		Visited.insert(make_pair(num[i], false));
	}
	sort(num.begin(), num.end());

	DFS(0);
	

	return 0;
}