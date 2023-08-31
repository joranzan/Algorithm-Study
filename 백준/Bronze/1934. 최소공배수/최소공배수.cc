#include<iostream>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T;
	cin >> T;
	for (int test = 0; test < T; test++)
	{

		int init_A, init_B;
		cin >> init_A >> init_B;
		if (init_A < init_B)
		{
			swap(init_A, init_B);
		}
		int A = init_A;
		int B = init_B;
		int residue;
		while (1)
		{
			residue = A % B;
			if (residue == 0) break;
			A = B;
			B = residue;
		}

		int LCM = B * (init_A / B) * (init_B / B);
		cout << LCM << "\n";

	}

	return 0;
}