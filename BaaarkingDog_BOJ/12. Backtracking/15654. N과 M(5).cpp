#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

	int N, M;
	cin >> N >> M;

	vector<int> input;
	vector<vector<int>> ans;
	int arr[10] = { 0, };

	for (int i = N-1; i > N-1-M; i--) {
		arr[i] = 1;
	}

	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		input.push_back(temp);
	}
	sort(input.begin(), input.end());

	do {
		vector<int> temp;
		for (int i = 0; i < N; i++) {
			if (arr[i] == 1) {
				temp.push_back(input[i]);
			}
			
		}

		do {
			ans.push_back(temp);

		}while (next_permutation(temp.begin(), temp.end()));

	}while (next_permutation(arr, arr + N));

	sort(ans.begin(), ans.end());

	for (int i = 0; i < ans.size(); i++) {
		for (int j = 0; j < ans[i].size(); j++) {
			cout << ans[i][j] << " ";
		}
		cout << "\n";
	}

	return 0;
}