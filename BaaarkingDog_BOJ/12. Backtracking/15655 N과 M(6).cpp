#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

	vector<int> Input;
	int arr[10] = { 0, };

	int N, M;
	cin >> N >> M;

	for (int i = M; i < N; i++) {
		arr[i] = 1;
	}
	

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		Input.push_back(num);
	}

	sort(Input.begin(), Input.end());

	//먼저 배열에서 0인애들만 뽑고 
	//수열만들어서 저장 -> 오름차순만 저장

	do {
		for (int i = 0; i < N; i++) {
			//내림차순 정렬
			//if (arr[i] == 0) cout << Input[N-1- i] << " ";

			//오름차순 정렬
			if (arr[i] == 0) cout << Input[i] << " ";

		}
		cout << "\n";
		

	} while (next_permutation(arr, arr + N));


	return 0;
}
