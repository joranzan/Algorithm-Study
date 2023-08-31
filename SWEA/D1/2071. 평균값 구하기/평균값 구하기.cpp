#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++)
	{
		vector<int> num(10);
		int sum = 0;
		int answer = 0;
		for (int i = 0; i < 10; i++)
		{
			cin >> num[i];
			sum += num[i];
		}
		if (sum % 10 < 5)
		{
			sum -= (sum % 10);
		}
		else
		{
			sum = sum - (sum % 10) + 10;
		}
		answer = sum / 10;
		cout << "#" << test << " " << answer << "\n";

	}
	
	return 0;
}