#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	long N;
	
	cin >> N;
	long result = N;
	for (long i = 2; i <= sqrt(N); i++)
	{
		if (N % i == 0)
		{
			//앞에 i의 배수들은 서로소가 아니므로 그만큼 개수 다 빼버리기
			result = result - (result / i);

			while (N % i == 0)
			{
				//소인수 제거
				N = N / i;
			}
		}
	}
	//소인수 존재
	if (N > 1)
	{
		result = result - (result / N);
	}

	cout << result << "\n";


	return 0;
}