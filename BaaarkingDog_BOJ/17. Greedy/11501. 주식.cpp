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

		//전역변수 Answer Test Case마다 초기화
		Answer = 0;
	}

	return 0;
}


/*

1. 주식 하나를 산다.
2. 원하는 만큼 가지고 있는 주식을 판다.
3. 아무것도 안한다.

*/


/*

최대일 때 팔아야함

1 1 3 1 2

3 3 3 2 2

2+2+0+1+0


10 7 6

10 7 6

0+0+0


3 5 9

9 9 9

6+4+0
*/