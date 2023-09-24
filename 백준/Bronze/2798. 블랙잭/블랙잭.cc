#include<iostream>
#include<vector>

using namespace std;

int N, M;
int Answer = 0;
vector<int> v;

void DFS(int index, int depth, int sum) {
	if (depth >= 3) {
		if (sum <= M) {
			Answer = max(Answer, sum);
		}
		return;
	}

	for (int i = index; i < N; i++) {
		if (sum + v[i] > M) continue;
		DFS(i + 1, depth + 1, sum + v[i]);
	}
}

int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		v.push_back(temp);
	}

	DFS(0, 0, 0);

	cout << Answer;


	return 0;
}