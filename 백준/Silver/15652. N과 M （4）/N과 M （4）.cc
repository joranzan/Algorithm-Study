#include<iostream>
#include<vector>

using namespace std;

int N, M;
vector<int> path;

void DFS(int index, int depth) {

	if (depth >= M) {
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = index; i <= N; i++) {
		path.push_back(i);
		DFS(i, depth + 1);
		path.pop_back();
	}

}

int main() {


	cin >> N >> M;

	DFS(1, 0);

	return 0;
}