#include<iostream>
#include<algorithm>

using namespace std;

int N, M;
int arrN[20000];
int arrM[20000];


void solution() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		int nowNum = arrN[i];
		if (nowNum <= arrM[0]) break;
		if (nowNum > arrM[M-1]) {
			cnt += M;
			continue;
		}
		
		cnt += (lower_bound(arrM, arrM + M, nowNum) - arrM);
	}
	cout << cnt << "\n";
}

void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arrN[i];
	}
	for (int i = 0; i < M; i++) {
		cin >> arrM[i];
	}

	sort(arrN, arrN + N, greater<int>());
	sort(arrM, arrM + M);

}







int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;

	for (int test = 0; test < T; test++) {
		
		input();
		solution();
	}



	return 0;
}