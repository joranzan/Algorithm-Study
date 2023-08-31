#include<iostream>
#include<queue>

using namespace std;

//각 줄기세포: 생명력 수치 X
// X시간 후 활성화 -> X시간 뒤에 죽음(셀에서 그대로 있긴함)

//활성화된 줄기세포
//상하좌우 번식 (1시간)
//겹칠 경우 생명력 수치가 높은 줄기세포가 차지(동시 인경우)


//K시간 후 살아있는 줄기 세포 (비활성 + 활성)    1이상 300이하

int Map[651][651] = { 0, };
int Visited[651][651] = { 0, };


struct Cell {

	int origin_life;   //기존 수명 X
	int current_life;  //현재 수명
	int state;  // 2: 활성화  1: 비활성화  0: 죽음
	
	int row;
	int col;

	bool operator<(Cell next) const {
		if (origin_life < next.origin_life) return true;
		if (origin_life > next.origin_life) return false;

		if (row < next.row) return false;
		if (row > next.row) return true;

		if (col < next.col) return false;
		if (col > next.col) return true;

		return false;		
	}

};


priority_queue<Cell> pq;

void FloodFill() {

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };

	priority_queue<Cell> pq_temp;

	//기존에 남은 pq에 있는 데이터 옮기기
	while (!pq.empty()) {
		pq_temp.push(pq.top());
		pq.pop();
	}

	while (!pq_temp.empty()) {

		Cell Now = pq_temp.top();
		pq_temp.pop();

		int next_life = Now.current_life - 1;  //1시간 지났다고 생각하고

		if (Now.state == 1) {  //비활성화 되어있다면

			//아직 대기시간이 남아있다면 비활성화 유지
			if (next_life > 0) {
				pq.push({ Now.origin_life, next_life, Now.state, Now.row, Now.col });
			}
			//대기시간이 끝나고 활성화 되어야하는 경우
			else {
				pq.push({ Now.origin_life, Now.origin_life, 2, Now.row,Now.col });
			}

		}
		else{   //이미 활성화 된 상태
			if (next_life > 0) //아직 수명남았다면
			{
				pq.push({ Now.origin_life, next_life, Now.state, Now.row, Now.col });
			}

			for (int i = 0; i < 4; i++) {
				int next_row = Now.row + dr[i];
				int next_col = Now.col + dc[i];

				if (next_row < 0 || next_col < 0 || next_row>650 || next_col>650) continue;
				if (Visited[next_row][next_col] == 1) continue;

				Visited[next_row][next_col] = 1;
				pq.push({ Now.origin_life, Now.origin_life, 1, next_row, next_col });
			}

		}

	}

}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//freopen_s(new FILE*, "input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int test = 1; test <= T; test++) {


		int N, M, K;
		cin >> N >> M >> K;

		//초기화
		for (int i = 0; i < 651; i++) {
			for (int j = 0; j < 651; j++) {
				Visited[i][j] = 0;
				Map[i][j] = 0;
			}
		}
		while (!pq.empty()) pq.pop();



		//입력
		for (int i = 300; i < 300 + N; i++) {
			for (int j = 300; j < 300 + M; j++) {
				cin >> Map[i][j];
				if (Map[i][j] == 0) continue;
				pq.push({ Map[i][j],Map[i][j],1,i,j });
				Visited[i][j] = 1;
			}
		}

		for (int i = 0; i < K; i++) {  //1시간 마다
			FloodFill();
		}

		cout << "#" << test << " " << pq.size() << "\n";

	}

	return 0;
}