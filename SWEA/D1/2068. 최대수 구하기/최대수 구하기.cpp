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
		for (int i = 0; i < 10; i++)
		{
			cin >> num[i];
		}
		int answer = *max_element(num.begin(),num.end());

		cout << "#" << test << " " << answer << "\n";

	}
	
	return 0;
}