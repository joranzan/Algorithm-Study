#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 0; test < T; test++)
	{
		cout << "#" << test+1 << "\n";
		int N;
		cin >> N;
		int cnt = 0;
		for (int i = 0; i < N; i++)
		{
			char c;
			int num;
			cin >> c >> num;

			for (int j = 0; j < num; j++)
			{
				
				cnt++;
				cout << c;
				if (cnt == 10)
				{
					cnt = 0;
					cout << "\n";
				}
			}
		}
		if (cnt != 0) cout << "\n";

	}

	return 0;
}