#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

//얻을 수 있는 점수
//상대방 점프일때
//(100000+100000) * K(100) * Q(4000) = 80,000,000,000 -> 800억
//상금 받을 때
//S(1000000) * Q(4000) = 4,000,000,000  -> 40억

//점수는 long int로 사용해야함

struct pos {
	//4개의 위치 우선순위
	//1. 행+열 큰 칸
	//2. 행 큰 칸
	//3. 열 큰 칸
	int row;
	int col;
	bool operator<(pos next) const {
		if (row + col < next.row + next.col) return true;
		else if (row + col > next.row + next.col) return false;
		else {
			if (row < next.row) return true;
			else if (row > next.row) return false;
			else {
				if (col < next.col) return true;
				else if (col > next.col) return false;
				else return false;
			}
		}
	}
};

struct Rabbit {

	//토끼의 정보
	//1. 고유 번호 pid
	//2. 필수 이동거리 d

	int Pid;   //고유번호
	int dist;  //이동거리
	int index; //배열 인덱스
};

struct Jump {
	//경주 진행 우선순위 순서
	//1. 현재까지 점프 횟수 적은 토끼
	//2. 현재 서있는 칸 (행+열) 작은 토끼
	//3. 행 번호 작은 토끼
	//4. 열 번호 작은 토끼
	//5. 고유번호 작은 토끼

	int jumpCnt;  //점프 횟수
	int row;
	int col;
	long score; //점수
	Rabbit info;

	bool operator<(Jump next) const {
		if (jumpCnt < next.jumpCnt) return false;
		else if (jumpCnt > next.jumpCnt) return true;
		else {
			if (row + col < next.row + next.col) return false;
			else if (row + col > next.row + next.col) return true;
			else {
				if (row < next.row) return false;
				else if (row > next.row) return true;
				else {
					if (col < next.col) return false;
					else if (col > next.col) return true;
					else {
						if (info.Pid < next.info.Pid) return false;
						else if (info.Pid > next.info.Pid) return true;
						else return false;
					}
				}
			}
		}
	}
};

struct addScore {

	//K번 턴 끝났을 때  (K번의 턴동안 한번이라도 뽑힌 토끼에 대해서만)
	//  -> 참여했는지 배열 만들기(participated)
	//점수 S 더하는 우선순위 
	//1. 현재 서있는 칸 (행+열) 큰 토끼
	//2. 행 번호 큰 토끼
	//3. 열 번호 큰 토끼
	//5. 고유번호 큰 토끼

	int row;
	int col;
	int Pid;
	int index;

	bool operator<(addScore next) const {
		if (row + col < next.row + next.col) return true;
		else if (row + col > next.row + next.col) return false;
		else {
			if (row < next.row) return true;
			else if (row > next.row) return false;
			else {
				if (col < next.col) return true;
				else if (col > next.col) return false;
				else {
					if (Pid < next.Pid) return true;
					else if (Pid > next.Pid) return false;
					else return false;
				}
			}
		}
	}
};

//P마리 토끼 (시작점: (1,1)) -> NxM 행렬 1,1부터
int Q;
int N, M, P;

Jump rabbitDAT[2000];  //토끼들 DAT
bool Jumped[2000] = { false, };  //뛰었는지 확인 배열

int changeDir(int dir) {
	if (dir == 0) {
		return 1;
	}
	else if (dir == 1) {
		return 0;
	}
	else if (dir == 2) {
		return 3;
	}
	else if (dir == 3) {
		return 2;
	}
}

void racestart(int K, int S) {

	//점프
	//i번 토끼의 d만큼 상하좌우
	//칸 벗어나면 방향을 반대로 바꿈 -> 현재 바라보는 dir 저장해놔야함
	priority_queue<Jump> pqJump;
	for (int i = 0; i < P; i++) {
		pqJump.push(rabbitDAT[i]);
	}
	
	long ScoreStacked = 0;

	const int dr[4] = { -1,1,0,0 };
	const int dc[4] = { 0,0,-1,1 };
	for (int i = 0; i < K; i++) {

		Jump Now = pqJump.top();
		pqJump.pop();
		Jumped[Now.info.index] = true;

		priority_queue<pos> candi;
		for (int dir = 0; dir < 4; dir++) {
			int distance = Now.info.dist;
			int next_r = Now.row + dr[dir] * (distance % (2 * (N - 1)));
			int next_c = Now.col + dc[dir] * (distance % (2 * (M - 1)));
			if (next_r <= 0) {
				next_r = 1 + (1 - next_r);
				if (next_r > N) {
					next_r = N - (next_r - N);
				}
			}
			if (next_r > N) {
				next_r = N - (next_r - N); 
				if (next_r <= 0) {
					next_r = 1 + (1 - next_r);
				}
			}
			if (next_c <= 0) {
				next_c = 1 + (1 - next_c);
				if (next_c > M) {
					next_c = M - (next_c - M);
				}
			}
			if (next_c > M) {
				next_c = M - (next_c - M);
				if (next_c <= 0) {
					next_c = 1 + (1 - next_c);
				}
			}
			candi.push({ next_r,next_c });
		}
		//점프했을 때 i번 토끼 제외 나머지 +=(행+열) 점수 얻음
		pos next = candi.top();
		ScoreStacked += (next.row + next.col);

		Now.row = next.row;
		Now.col = next.col;
		Now.jumpCnt++;
		Now.score -= (next.row + next.col);

		rabbitDAT[Now.info.index] = Now;
		pqJump.push(Now);
		//int debugging = -1;
	}
	priority_queue<addScore> pqScore;

	for (int i = 0; i < P; i++) {
		rabbitDAT[i].score += ScoreStacked;
		if (!Jumped[i]) continue;
		pqScore.push({ rabbitDAT[i].row, rabbitDAT[i].col, rabbitDAT[i].info.Pid, i });
	}
	rabbitDAT[pqScore.top().index].score += S;


	int debugging = -1;

}

void init() {
	for (int i = 0; i < P; i++) {
		Jumped[i] = false;
	}
}

void solution() {

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		int cmd;
		cin >> cmd;
		if (cmd == 100) {  //입력
			cin >> N >> M >> P;
			for (int j = 0; j < P; j++) {
				int id, dist;
				cin >> id >> dist;
				Jump temp = { 0,1,1,0, {id, dist, j} };
				rabbitDAT[j] = temp;
			}
		}
		else if (cmd == 200) { //경주
			int K, S;
			cin >> K >> S;
			init(); //Jumped 배열 초기화
			racestart(K, S);
		}
		else if (cmd == 300) { //거리 조정
			int id, L;
			cin >> id >> L;
			for (int i = 0; i < P; i++) {
				if (rabbitDAT[i].info.Pid == id) {
					rabbitDAT[i].info.dist *= L;
					break;
				}
			}
		}
		else if (cmd == 400) { //정답 출력
			
			long Ans = 0;
			for (int i = 0; i < P; i++) {
				Ans = max(Ans, rabbitDAT[i].score);
			}
			cout << Ans << "\n";
			break;
		}
	}

}


int main() {

	solution();

	return 0;
}

//토끼고유번호가 너무 크므로 구조체에 고유번호 넣고 그냥 배열[2000]로 해야할듯
//뛸때마다 우선순위 체크해야함



// 이동거리 변경
// 특정 고유번호 t에 대해 이동거리 L배 하기 (10억 안넘으니까 ㄱㅊ)


// 얻은 점수 중 가장 높은 점수 출력 (경주마다 초기화 안됨)