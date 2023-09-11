#include<iostream>
#include<vector>

using namespace std;

int N, M;
vector<int> ans;
bool Visited[9] = { false, };

void DFS(int depth) {

	if (depth == M) {
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i] << " ";
		}
		cout << "\n";
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (Visited[i]) continue;  //백트래킹?
		Visited[i] = true;
		ans.push_back(i);
		DFS(depth + 1);
		Visited[i] = false;
		ans.pop_back();
	}

}


int main() {

	cin >> N >> M;

	DFS(0);

	return 0;
}