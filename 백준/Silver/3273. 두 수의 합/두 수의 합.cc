#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

	int N, X;
	cin >> N;

	vector<int> v(N);

	for (int i = 0; i < N; i++) {

		cin >> v[i];

	}
	cin >> X;

	sort(v.begin(), v.end());

	int left = 0;
	int right = N - 1;
	int Answer = 0;

	while (left < right && right < N) {

		int sum = v[left] + v[right];

		if (sum < X) left++;
		else if (sum > X) right--;
		else if (sum == X) {
			Answer++;

			//cout << v[left] << " " << v[right] << "\n";

			left++;
			right--;
			
		}


	}
	cout << Answer;


	return 0;
}