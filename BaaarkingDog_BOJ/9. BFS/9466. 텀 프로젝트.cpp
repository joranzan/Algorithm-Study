#include<iostream>
#include<stack>

//�ٽ�Ǯ���


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

				//����Ŭ ����
				if (searched[now] == -2 || searched[now]==1) {
					valid = false;
					break;
				}
				//����Ŭ ã��
				if (searched[now] == -1) {
					//����Ŭ�� ������
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
			//����Ŭ ����
			else {
				//����Ŭ�� ������
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

�ٽ� : ����Ŭ ���� ���� �Ǵ�

�ʿ��� �ڷᱸ��

�׷����� Ȯ�� �迭 (�̹� �׷� ã�Ҵ°�? �ƴϸ� �̹� Ž���ߴµ� ��ã�Ҵ°�?)
input �迭


*/