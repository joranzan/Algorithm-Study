#include<iostream>
#include<vector>

using namespace std;

int N, M;
vector<int> num;

void DFS(int depth, int index) {

	if (depth >= M) {
		for (int i = 0; i < num.size(); i++) {
			cout << num[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = index; i <= N; i++) {
		num.push_back(i);
		DFS(depth + 1, i + 1);
		num.pop_back();
	}

}

int main() {

	cin >> N >> M;

	DFS(0, 1);

	return 0;
}