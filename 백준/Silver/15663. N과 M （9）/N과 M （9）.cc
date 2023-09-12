#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;


int N, M;
int Input[10] = { 0, };   //해당 인덱스와 입력 숫자 매핑
vector<int> Answer; //고른 숫자를 넣을 배열
bool Visited[10] = { 0, };  //해당 인덱스를 방문했는지 여부


void DFS(int depth) {
	if (depth >= M) {
		for (int i = 0; i < M; i++) {
			cout << Answer[i] << " ";
		}
		cout << "\n";
		return;
	}
	int lastNum = 0;

	for (int i = 0; i < N; i++) {   //0번 인덱스부터 N-1인덱스까지
		if (Visited[i] == 1) continue; //해당 인덱스 방문했다면 무시
		if (Input[i] == lastNum) continue; //인덱스는 다르지만 값이 같은 경우 무시
		
		
		//마지막 숫자 갱신(다음 인덱스에도 같은 숫자일 수도 있기 때문에 처리하기 위해서)
		lastNum = Input[i];    
		
		Visited[i] = true;
		Answer.push_back(Input[i]); //정답 배열에 골라서 넣기
		
		DFS(depth + 1);

		Visited[i] = false;
		Answer.pop_back();


	}

}


int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		
		cin >> Input[i];
	}
	sort(Input, Input + N);

	DFS(0);


	return 0;
}

