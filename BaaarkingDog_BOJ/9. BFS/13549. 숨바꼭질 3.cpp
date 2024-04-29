#include<iostream>
#include<queue>

using namespace std;

int N, K;
int Visited[100001] = { 0, };



void BFS() {
	queue<int> q;
	q.push(N);
	Visited[N] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		if (now == K) {
			cout << Visited[now] - 1;
			break;
		}

		if (now * 2 <= 100000) {
			if (Visited[now * 2] == 0) {
				Visited[now * 2] = Visited[now];
				q.push(now * 2);
			}
			else {
				if (Visited[now] < Visited[now * 2]) {
					Visited[now * 2] = Visited[now];
				}
			}
		}
		if (now - 1 >= 0) {
			if (Visited[now - 1] == 0) {
				Visited[now - 1] = Visited[now] + 1;
				q.push(now - 1);
			}
			else{
				if (Visited[now] + 1 < Visited[now - 1]) {
					Visited[now - 1] = Visited[now] + 1;
				}
			}
		}

		if (now + 1 <= 100000) {
			if (Visited[now + 1] == 0) {
				Visited[now + 1] = Visited[now] + 1;
				q.push(now + 1);
			}
			else {
				if (Visited[now] + 1 < Visited[now + 1]) {
					Visited[now + 1] = Visited[now] + 1;
				}
			}
		}
		
	}
}


void DP() {

	for (int i = N - 1; i >= 0; i--) {
		Visited[i] = N - i;
	}
	for (int i = N + 1; i <= 100000; i++) {
		Visited[i] = i - N;
	}

	for (int i = 0; i <= 50000; i++) {
		if (Visited[i] < Visited[i * 2]) Visited[i * 2] = Visited[i];
	}

	int debugging = -1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> K;

	//Ǯ�� 1
	BFS();

	//Ǯ�� 2 (�Ұ���)  �ڷ� ���� �͵� �ֱ� ������ �ð� �� �ɸ�
	//DP();

	//Ǯ�� 3 : ���ͽ�Ʈ�� -> �ð� �� �ɸ�...

	return 0;
}

/*
���� �м�



*/