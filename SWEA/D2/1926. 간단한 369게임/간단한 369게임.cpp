#include<iostream>
#include<vector>


using namespace std;

bool previous = false;

void Recursion(int n)
{
	if (n == 0) return;
	int res = n % 10;
	int mok = n / 10;
	Recursion(mok);
	
	if (res % 3 == 0 && res != 0)
	{
		cout << "-";
		previous = true;
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++)
	{
		previous = false;
		Recursion(i);
		if (!previous) cout << i;
		cout << " ";
	}


	return 0;
}