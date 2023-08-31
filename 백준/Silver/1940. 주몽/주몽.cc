#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, M;
	cin >> N >> M;
	vector<int> Num;
	Num.resize(N);

	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}
	int start = 0, end = N - 1;
	int count = 0;
	sort(Num.begin(), Num.end());
	while (start < end)
	{
		if (Num[start] + Num[end] == M)
		{
			count++; end--; start++;
		}
		else if (Num[start] + Num[end] > M)
		{
			end--;
		}
		else
		{
			start++;
		}

	}

	cout << count << "\n";

	return 0;
}