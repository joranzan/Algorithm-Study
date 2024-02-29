#include<iostream>

using namespace std;

int Score[101] = { 0, };

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	int Answer = 0;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Score[i];
	}

	for (int i = N - 2; i >= 0; i--) {
		
		if (Score[i] >= Score[i + 1]) {
			int decreased = Score[i] - (Score[i + 1] - 1);
			Score[i] = Score[i + 1] - 1;
			Answer += decreased;
		}

	}
	
	cout << Answer;

	return 0;
}

/*

게임 정보

N개의 Level
- 온라인 순위 (레벨 클리어 할 때 얻은 점수의 합 기준)
- 레벨을 난이도 순 배치 (점수 획득 안맞음)


목표 : 각 레벨을 클리어할 때 얻는 점수 상승

- 특정 레벨의 점수 감소시킴


점수 조건

- 점수 > 0
- 1만큼 감소 : 1번
- 최소한으로 점수 내리기

출력 : 몇 번 감소?


*/


/*

점수를 감소시키기만 하므로 마지막 레벨 부터 내리면 됨

현재 레벨의 점수가
1) 다음 레벨의 점수보다 작으면 감소 필요 X
2) 다음 레벨의 점수보다 크거나 같으면
(다음 레벨의 점수 - 1)로 만들기 위해 감소해야하는 횟수 계산
Answer에 추가

TC 1 

5 5 5

3 4 5


TC 2

5 3 7 5

2 3 4 5
-3	-3

*/