#include<iostream>
#include<stack>

using namespace std;

int inputData[100001] = { 0, };
int searched[100001] = { 0, };
int N;


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {



		cin >> N;

		for (int i = 1; i <= N; i++) {
			cin >> inputData[i];
			searched[i] = 0;
		}

		for (int i = 1; i <= N; i++) {

			if (searched[i] != 0) continue;

			int now = i;
			bool valid = true;
			stack<int> s;
			while (searched[now] == 0) {
				searched[now] = -1;
				s.push(now);
				now = inputData[now];

				//사이클 없음
				if (searched[now] == -2 || searched[now]==1) {
					valid = false;
					break;
				}
				//사이클 찾음
				if (searched[now] == -1) {
					//사이클의 시작점
					s.push(now);
					break;
				}
			}

			int debugging1 = -1;

			if (!valid) {
				while (!s.empty()) {
					int tempnow = s.top();
					s.pop();
					searched[tempnow] = -2;
				}
			}
			//사이클 있음
			else {
				//사이클의 시작점
				int endpoint = s.top();
				s.pop();

				int trigger = 1;

				while (!s.empty()) {
					int tempnow = s.top();
					s.pop();

					searched[tempnow] = trigger;

					if (tempnow == endpoint) trigger = -2;

				}
			}
		}

		int Answer = 0;

		for (int i = 1; i <= N; i++) {
			if (searched[i] == 1) Answer++;
		}

		Answer = N - Answer;

		cout << Answer << "\n";

	}

	return 0;
}

/*

핵심 : 사이클 존재 여부 판단

필요한 자료구조

그룹존재 확인 배열 (이미 그룹 찾았는가? 아니면 이미 탐색했는데 못찾았는가?)
input 배열


*/