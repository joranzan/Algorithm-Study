#include<iostream>
#include<vector>
#include<cmath>


using namespace std;

// 각 계란: 내구도 , 무게
// 내구도 0 이하 -> 깨짐 (상대 계란 무게만큼 깎임)
// 
// 퍼즐 목표 : 최대한 많은 계란을 깨기
//1. 일렬로 놓인 계란 왼쪽부터 선택
//2. 깨지지 않은 계란 하나 선택해서 침
//3. 손에 든 계란 깨졌거나, 깨지지 않은 다른 계란 없으면 continue;
//4. 계란 내려놓음
//5. 다음칸 계란 들고 과정 반복


//입력
//N: 계란의 수 1이상 8이하
//내구도 무게



struct egg {
	int hard;
	int weight;
};

int N;
egg eggs[10] = {};
bool isBroken[10] = { false }; //계란이 깨졌는지 여부
int Answer = 0;


void BackTracking(int depth, int cnt) {

	if (depth >= N || cnt== N) {   //가장 오른쪽 계란에 도달한 경우 OR cnt가 이미 계란 다 깬 상태
		Answer = max(Answer, cnt);
		return;
	}
	

	if (isBroken[depth]) BackTracking(depth + 1, cnt);  //선택한 계란 이미 깨진상태면 넘김
	else {
		if (cnt == N - 1) {   //자기 빼고 다 깨진 상태이면 그냥 return 어차피 더 못깸
			Answer = max(Answer, cnt); 
			return;
		}

		for (int i = 0; i < N; i++) {
			if (depth == i) continue;  //자기 자신 깨는 경우 무시
			if (isBroken[i]) continue; //이미 깨진 계란 선택했으면 무시

			int nowCnt = cnt;

			//계란 깨뜨리는 연산 과정
			int hard1 = eggs[depth].hard;
			int weight1 = eggs[depth].weight;
			int hard2 = eggs[i].hard;
			int weight2 = eggs[i].weight;

			int after_hard1 = hard1 - weight2;
			int after_hard2 = hard2 - weight1;

			if (after_hard1 <= 0) {
				nowCnt++;
				isBroken[depth] = true;
			}
			if (after_hard2 <= 0) {
				nowCnt++;
				isBroken[i] = true;
			}

			eggs[depth].hard = after_hard1;
			eggs[i].hard = after_hard2;

			BackTracking(depth + 1, nowCnt);

			eggs[depth].hard = hard1;
			eggs[i].hard = hard2;
			isBroken[depth] = false;
			isBroken[i] = false;
		}
	}

}


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		int hard, weight;
		cin >> hard >> weight;
		eggs[i] = { hard,weight };
	}

	BackTracking(0, 0);
	cout << Answer;

	return 0;
}

// 계란 0 계란1 계란 2
//계란 0 선택
// 1 치기, 2치기 중 선택
// 1친경우: 