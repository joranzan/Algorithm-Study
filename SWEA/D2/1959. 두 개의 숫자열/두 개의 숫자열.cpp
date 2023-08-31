#include<iostream>
#include<vector>


using namespace std;


/*void Recursion(int n)
{
	if (n / 10 ==0)
	{
		cout << n;
		return;
	}
	n = n / 10;
	Recursion(n);
	cout << n;
}*/


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	for (int test = 1; test <= T; test++)
	{
		int N, M;
		cin >> N >> M;

		vector<int> A(N);
		vector<int> B(M);
		int answer = -999999999;
		for (int i = 0; i < N; i++) cin >> A[i];

		for (int i = 0; i < M; i++) cin >> B[i];


		if (N == M)
		{
			int sum = 0;
			for (int i = 0; i < N; i++)
			{
				sum = sum + (A[i] * B[i]);
			}
			cout << sum;
			return 0;
		}
		for (int i = 0; i <= abs(N - M); i++)
		{
			int sum = 0;
			if (N > M)
			{
				for (int j = 0; j < M; j++)
				{
					int temp = A[j + i] * B[j];
					sum += temp;
				}
			}
			else if (N < M)
			{
				for (int j = 0; j < N; j++)
				{
					int temp = A[j] * B[j + i];
					sum += temp;
				}
			}
			answer = max(answer, sum);
		}
		cout << "#" << test << " " << answer << "\n";
	}


	return 0;
}