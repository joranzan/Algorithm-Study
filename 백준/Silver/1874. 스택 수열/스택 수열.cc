#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int main()
{
	//ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	vector<char> Result;
	vector<int> Num(N + 1, 0);
	stack<int> myStack;
	for (int i = 1; i <= N; i++)
	{
		cin >> Num[i];
	}

	int push_num = 1;
	bool no_way = true;

	for (int i = 1; i <= N; i++)
	{
		if (push_num <= Num[i])
		{
			myStack.push(push_num);
			push_num++;
			Result.push_back('+');
			while (myStack.top() != Num[i])
			{
				myStack.push(push_num);
				push_num++;
				Result.push_back('+');

			}
			myStack.pop();
			Result.push_back('-');
		}
		else
		{
			if (myStack.top() == Num[i])
			{
				myStack.pop();
				Result.push_back('-');
				
			}
			else
			{
				no_way = false;
				cout << "NO\n";
				break;
			}
		}
	}
	if (no_way)
	{
		for (int i = 0; i < Result.size(); i++)
		{
			cout << Result[i] << "\n";
		}
	}

	return 0;
}