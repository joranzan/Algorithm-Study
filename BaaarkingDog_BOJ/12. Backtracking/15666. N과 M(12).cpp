#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, M;
int arr[10] = { 0, };
vector<int> Ans;

void DFS(int index, int depth) {

	if (depth >= M) {
		for (int i = 0; i < Ans.size(); i++) {
			cout << Ans[i] << " ";
		}
		cout << "\n";
		return;
	}

	int prev = -1;

	for (int i = index; i < N; i++) {
		if (prev == arr[i]) continue;
		prev = arr[i];
		Ans.push_back(arr[i]);
		DFS(i, depth + 1);
		Ans.pop_back();
	}
}


int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);

	DFS(0, 0);

	return 0;
}