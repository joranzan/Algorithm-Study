#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, M;
int arr[10] = { 0 };
bool Visited[10] = { false, };
vector<int> path;

void DFS(int index, int depth) {

	if (depth >= M) {
		for (int i = 0; i < M; i++) {
			cout << path[i] <<" ";
		}
		cout << "\n";
		return;
	}

	int prev = 0;

	for (int i = index; i < N; i++) {
		if (Visited[i]) continue;
		if (prev == arr[i]) continue;
		prev = arr[i];
		Visited[i] = true;
		path.push_back(arr[i]);
		DFS(i + 1, depth + 1);
		Visited[i] = false;
		path.pop_back();
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

//N개의 자연수 중 M개 고른 수열

//조건
//오름차순 (같은 애들 존재)
//

//중복되는 수열 여러번 출력 X