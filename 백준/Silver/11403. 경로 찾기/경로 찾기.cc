#include<iostream>
#include<vector>

using namespace std;

//문제분석

//가중치 x  방향 그래프
//모든 정점 (i,j) 
//i에서 j로 가는 길이가 양수인 경로 여부

int N;
vector<int> Adj[101];
int Visited[101] = { 0, };

void DFS(int now) {
	if (Adj[now].size() == 0) return;

	for (int i = 0; i < Adj[now].size(); i++) {
		int next = Adj[now][i];
		if (Visited[next] == 1) continue;
		Visited[next] = 1;
		DFS(next);
	}
	
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int temp;
			cin >> temp;
			if (temp == 1) Adj[i].push_back(j);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) Visited[j] = 0;
		
		DFS(i);
		for (int j = 1; j <= N; j++) cout << Visited[j] << " ";
		cout << "\n";
	}
	

	return 0;
}