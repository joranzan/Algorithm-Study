#include<iostream>
#include<vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	long int N;
	vector<long int> A;
	long int B, C;
	long long int sum = 0;

	cin >> N;
	A.resize(N);
	for (long int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	cin >> B >> C;

	for (long int i = 0; i < N; i++)
	{
		if (A[i] > B)
		{
			sum++;
			long long int need_C;
			need_C = (A[i]-B) / C;
			int r = (A[i] - B) % C;
			if(r!=0) need_C += 1;
			sum += need_C;		
		}
		else
		{
			sum++;
		}
	}
	cout << sum << "\n";

	return 0;
}