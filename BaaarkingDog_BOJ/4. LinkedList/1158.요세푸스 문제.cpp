#include<iostream>
#include<vector>

using namespace std;

struct Node {
	struct Node* next;
	int data;
};

int N, K;

int main() {

	cin >> N >> K;
	
	vector<vector<int>> v(3, vector<int>(N + 1, 0));  //data prev next

	for (int i = 1; i <= N; i++) {
		v[0][i] = i;
		if (N == 1) {
			cout << "<1>"; 
			return 0;
		}
		if (i == 1) {
			v[1][i] = N;
			v[2][i] = i + 1;
		}
		else if (i == N) {
			v[1][i] = i - 1;
			v[2][i] = 1;

		}
		else {
			v[1][i] = i - 1;
			v[2][i] = i + 1;
		}
	}

	int start = K;
	int cnt = 1;
	cout << "<";

	while (v[1][start] != 0 || v[2][start] != 0)
	{
		cout << v[0][start] ;
		v[0][start] = 0;
		v[1][v[2][start]] = v[1][start];
		v[2][v[1][start]] = v[2][start];
		int next = v[2][start];//기존에 있던 현재노드의 다음
		if (next == 0) break;

		v[1][start] = 0;
		v[2][start] = 0;
		cnt++;


		start = next;
		

		for (int i = 0; i < K-1; i++) {
			start = v[2][start];
		}
		if (v[1][start] != 0 || v[2][start] != 0) cout << ", ";
	}
	cout << ">";

	//cout << cnt;

	return 0;
}