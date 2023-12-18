#include<iostream>

using namespace std;

struct info {
	int volume;
	int cost;
};

int N, K;
info Stuff[101];

int Answer = 0;

//1-1. 기본 백트래킹으로 풀어보기
//시간복잡도 : 2^N -> 2의 100승 -> 시간 초과

void BackTracking1(int now, int vsum, int csum) {
	//백트래킹
	if (vsum > K) return;

	//기저조건
	if (now == N) {
		Answer = max(Answer, csum);
		return;
	}
	
	BackTracking1(now + 1, vsum + Stuff[now].volume, csum + Stuff[now].cost);
	BackTracking1(now + 1, vsum, csum);
}

//1-2. 백트래킹 (더 좋은 방법)
//now번째 물건을 보고 있고
//vsum만큼 담은 상태에서 얼마나 더 담을 수 있는지?
//앞으로 담을 수 있는 최대 가치 (K-vsum)
int BackTracking2(int now, int vsum) {
	
	if (vsum > K) return -1000000;
	if (now > N) return 0;

	/*if (Stuff[now].volume > K - vsum) {
		return BackTracking2(now + 1, vsum + Stuff[now].volume);
	}*/

	return max(BackTracking2(now + 1, vsum + Stuff[now].volume) + Stuff[now].cost, BackTracking2(now + 1, vsum));
}


//중복되는 케이스 : BackTracking2(now, vsum)의 return은 동일한 now와 vsum을 갖는 경우 모두 동일
//-> 계속 계산할 필요없이 Memoization!!


//여기까지 구현했으면 Top-Down은 쉽게 가능


//2. 중복되는 케이스들 Memoization으로 풀기
/*
ex) 3번을 보고 있고 이미 10만큼 담았음
0번 무게: 10
1번 무게 : 3
2번 무게 : 7
뭘 선택하던 3번을 바라보는 시점에서
앞으로 담을 수 있는 가치는 변하지 않음 
앞에 담은 무게
3  -> K-3
7  -> K-7
10 -> K-10
뒤에는 어차피 정해진 남은 무게 안에서 최대 찾아야함
*/



//int DP[바라보는 시점][남은 무게의 크기]
int DP[101][100001] = { 0, };

int TopDown(int now, int vsum) {

	if (vsum > K) return -100000;
	if (now > N) return 0;
	
	if (DP[now][vsum] != 0) return DP[now][vsum];

	DP[now][vsum] = max(TopDown(now + 1, vsum + Stuff[now].volume) + Stuff[now].cost, TopDown(now + 1, vsum));
	return DP[now][vsum];
}





//3. Bottom-up 풀어보기

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T = 1;
	//cin >> T;
	for (int test = 1; test <= T; test++) {
		cin >> N >> K;

		for (int i = 1; i <= N; i++) {
			cin >> Stuff[i].volume >> Stuff[i].cost;
		}

		//BackTracking1(1, 0, 0);
		//Answer = BackTracking2(1, 0);
		Answer = TopDown(1, 0);

		cout << Answer;
	}


	return 0;
}