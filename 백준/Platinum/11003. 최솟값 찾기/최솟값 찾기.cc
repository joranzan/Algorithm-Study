#include<iostream>
#include<vector>
#include<deque>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N, L;
	deque < pair<int, int>> mydeque;
	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		int now;
		cin >> now;

		while (!mydeque.empty()&&mydeque.back().second > now)
		{
			mydeque.pop_back();
		}	
		mydeque.push_back(make_pair(i, now));

		if (mydeque.front().first <= (i - L))
		{
			mydeque.pop_front();
		}	
			
		
		cout << mydeque.front().second << ' ';


	}
	return 0;
}