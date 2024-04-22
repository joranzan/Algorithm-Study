#include<iostream>

using namespace std;

int N, W, L;
int nowTime = 0;
int Bridge[101] = { 0, };
int Truck[1001] = { 0, };



void init() {
	cin >> N >> W >> L;
	for (int i = 1; i <= N; i++) {
		cin >> Truck[i];
	}
}

pair<int,int> onBridge() {
	int sum = 0;
	int cnt = 0;

	for (int i = 1; i <= W; i++) {
		
		if (Bridge[i] == 0) continue;
		Bridge[i - 1] = Bridge[i];
		Bridge[i] = 0;
	}

	for (int i = 1; i <= W; i++) {

		if (Bridge[i] == 0) continue;
		sum += Truck[Bridge[i]];
		cnt++;
	}

	
	
	return { sum, cnt };
}

void solution() {

	int nowIndex = 1;
	while (Bridge[0] != N) {
		nowTime++;
		pair<int,int> p = onBridge();
		int nowWeight = p.first;
		int nowCnt = p.second;
		if (nowCnt >= W) continue;
		if (Truck[nowIndex] + nowWeight > L) continue;
		Bridge[W] = nowIndex;
		nowIndex++;
	}
	
	cout << nowTime;

}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();


	return 0;
}

/*
문제 분석

N개의 트럭

1) 순서 못바꿈
2) 무게 서로 같지 않을 수 있음
3) W대의 트럭만 올라갈 수 있음


최대 하중 : L



*/