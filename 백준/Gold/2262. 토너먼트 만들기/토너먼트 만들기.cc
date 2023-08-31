#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	vector<int> Player(N + 1, 0);
	for (int i = 1; i <= N; i++)
	{
		cin >> Player[i];
	}

	int answer = 0;

	for (int i = N; i >= 3; i--)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Player[j] == i)
			{
				if (j == 1)
				{
					answer += abs(Player[j] - Player[j + 1]);
				}
				else if (j == Player.size()-1)
				{
					answer += abs(Player[j] - Player[j - 1]);
				}
				else
				{
					answer += abs(Player[j] - max(Player[j - 1], Player[j + 1]));
				}
				Player.erase(Player.begin() + j);
				break;
			}			
		}
	}
	if (N == 1) cout << "0\n";
	else cout << answer + 1 << "\n";
	return 0;
}