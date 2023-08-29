#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int N;
	cin >> N;
	vector<int> Num(N, 0);

	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}

	sort(Num.begin(), Num.end());
	
	int count = 0;

	for (int find = 0; find < N; find++)
	{
		int start = 0;
		int end = N - 1;

		while (start < end)
		{
			if (Num[start] + Num[end] == Num[find])
			{
				if (start != find && end != find)
				{
					count++;
					break;
				}
				else if (start == find)
				{
					start++;
				}
				else if (end == find)
				{
					end--;
				}
			}
			else if (Num[start] + Num[end] > Num[find])
			{
				end--;
			}
			else
			{
				start++;
			}
		}
	}
	cout << count << "\n";
	return 0;
}