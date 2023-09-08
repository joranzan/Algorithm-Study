#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	
	vector<int> Num(N, 0);
	vector<int> Answer(N, 0);
	stack<int> myStack;

	for (int i = 0; i < N; i++)
	{
		cin >> Num[i];
	}

	myStack.push(0);
	for (int i = 1; i < N; i++)
	{
		while (!myStack.empty() && Num[myStack.top()] < Num[i])
		{
			Answer[myStack.top()] = Num[i];
			myStack.pop();
		}
		myStack.push(i);
	}

	while (!myStack.empty())
	{
		Answer[myStack.top()] = -1;
		myStack.pop();
	}

	for (int i = 0; i < Answer.size(); i++)
	{
		cout << Answer[i] << " ";
	}

	return 0;
}
