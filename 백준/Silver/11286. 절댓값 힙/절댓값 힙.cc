#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct compare
{
	bool operator() (const int o1, const int o2)
	{
		int abs_o1 = abs(o1);
		int abs_o2 = abs(o2);
		if (abs_o1 == abs_o2)
		{
			return o1 > o2;      //절대값이 같을 때는 음수 우선 정렬
		}
		return abs_o1 > abs_o2;
	}
};

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	
	int N;
	priority_queue<int, vector<int>, compare> myQueue;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		if (x == 0)
		{
			if (myQueue.empty())
			{
				cout << "0\n";
			}
			else
			{
				cout << myQueue.top() << "\n";
				myQueue.pop();
			}
		}
		else
		{
			myQueue.push(x);
		}
	}
	return 0;
}