#include<iostream>
#include<string>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	
	for (int test = 0; test < T; test++)
	{
		string mystr;
		cin >> mystr;
		int sum = 0;
		int correct = 0;
		for (int i = 0; i < mystr.length(); i++)
		{
			char c = mystr[i];
			if (c == 'O')
			{
				correct++;
				sum += correct;				
			}
			else
			{
				correct = 0;
			}
		}
		cout << sum << "\n";
	}
	return 0;
}