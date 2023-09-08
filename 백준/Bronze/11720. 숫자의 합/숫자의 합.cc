#include<iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	string Numbers;
	cin >> Numbers;
	
	int sum = 0;

	for (int i = 0; i < Numbers.size(); i++)
	{
		sum += Numbers[i] - '0';
	}

	cout << sum << "\n";
	return 0;
}