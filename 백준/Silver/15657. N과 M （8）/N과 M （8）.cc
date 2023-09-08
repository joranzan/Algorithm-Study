#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, M;
vector<int> num;
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
		if (cnt==0)
		{
			Result[cnt] = num[i];
			DFS(cnt + 1);
		}
		else
		{
			if (Result[cnt - 1] > num[i])
				continue;
			Result[cnt] = num[i];
			DFS(cnt + 1);
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
	}
	sort(num.begin(), num.end());

	DFS(0);
	
	return 0;
}