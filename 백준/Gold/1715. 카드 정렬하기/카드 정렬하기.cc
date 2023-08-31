#include<iostream>
#include<queue>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	priority_queue<int, vector<int>, greater<int>> myQueue;
	int N, sum = 0, temp;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		myQueue.push(temp);
	}

	int data1 = 0;
	int data2 = 0;

	if (N == 1)
	{
		data1 = myQueue.top();
		myQueue.pop();
		cout << "0\n";
	}
	else if (N == 2)
	{
		data1 = myQueue.top();
		myQueue.pop();
		data2 = myQueue.top();
		myQueue.pop();
		cout << data1 + data2 << "\n";
	}
	else
	{
		while (myQueue.size() != 1)
		{
			data1 = myQueue.top();
			myQueue.pop();
			data2 = myQueue.top();
			myQueue.pop();
			sum += (data1 + data2);
			myQueue.push(data1 + data2);
		}
		cout << sum << "\n";
	}
	return 0;
}