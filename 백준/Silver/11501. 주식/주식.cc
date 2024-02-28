#include<iostream>

using namespace std;

int N;
long Answer = 0;
int maxValue[1000001] = { 0, };
int inputValue[1000001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T;
	cin >> T;
	
	for (int test = 0; test < T; test++) {

		cin >> N;

		for (int i = 0; i < N; i++) cin >> inputValue[i];

		int nowMax = 0;


		//해당 날짜로부터 미래까지 주식값 중 최고점 저장
		for (int i = N - 1; i >= 0; i--) {
			if (nowMax < inputValue[i]) {
				nowMax = inputValue[i];

			}
			maxValue[i] = nowMax;
		}

		
		for (int i = 0; i < N; i++) {
			//당일 주식값이 고점이면 넘김
			if (inputValue[i] == maxValue[i]) continue;
			//앞으로 고점에서 팔 때 차익
			Answer += (maxValue[i] - inputValue[i]);
		}

		cout << Answer << "\n";

		//전역변수 Answer TC마다 초기화
		Answer = 0;
	}

	return 0;
}
