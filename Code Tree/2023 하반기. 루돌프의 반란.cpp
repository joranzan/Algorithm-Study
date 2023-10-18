#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct santa {
	int row;
	int col;
	int score;
	int stun;
	bool valid;
};

struct candi {
	santa s;
	int dist;

	bool operator<(candi next) const {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			if (s.row < next.s.row) return true;
			else if (s.row > next.s.row) return false;
			else {
				if (s.col < next.s.col) return true;
				else if (s.col > next.s.col) return false;
				else return false;
			}
		}
	}
};

struct selection {
	int dist;
	int dir;
	bool operator<(selection next) const {
		if (dist < next.dist) return false;
		else if (dist > next.dist) return true;
		else {
			if (dir < next.dir) return false;
			else if (dir > next.dir) return true;
			else return false;
		}
	}
};
//대각선도 1칸으로 취급 (??? : 거리는 다른데)
const int dr[8] = { -1,0,1,0,-1,1,-1,1 };
const int dc[8] = { 0,1,0,-1,-1,-1,1,1 };

//1. 게임판의 구성
//N x N 크기의 격자
//(1,1) 부터 (r,c)
//게임은 M개의 턴에 걸쳐 진행(루돌프(한번 움직인 뒤), 산타(P명) 한번씩 움직임)
// 칸 사이의 거리 : (r1-r2)^2 + (c1-c2)^2 (int 안넘음)

int Map[51][51];
int N, M, P, C, D;
int RD_r, RD_c;
int RD_dir;
santa Santa[1001];   //산타 정보 배열
int reverseDir(int dir);

void Collision(int dir, int num) {  //충돌
	
	int santa_num = Map[RD_r][RD_c];
	if (!Santa[santa_num].valid) return;
	int rDir = reverseDir(dir);
	while (1) {
		//While문 사용
		int next_r, next_c;
		if (Map[RD_r][RD_c] == santa_num) {
			//루돌프 박은 후 C만큼 날라간 뒤 기절
			Santa[santa_num].stun = 2;
			next_r = Santa[santa_num].row + num * dr[rDir];
			next_c = Santa[santa_num].col + num * dc[rDir];
		}
		else {
			next_r = Santa[santa_num].row + dr[rDir];
			next_c = Santa[santa_num].col + dc[rDir];
		}

		//break조건  
		//1) 밖으로 날아간 경우(탈락)
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) {
			Santa[santa_num].valid = false;
			break;
		}
		//2) 산타없는 경우
		if (Map[next_r][next_c] == 0) {
			if (Map[RD_r][RD_c] == santa_num) {
				Map[Santa[santa_num].row][Santa[santa_num].col] = 0;
			}
			Map[next_r][next_c] = santa_num;
			Santa[santa_num].row = next_r;
			Santa[santa_num].col = next_c;
			break;
		}
		else if (!Santa[Map[next_r][next_c]].valid) {
			Map[Santa[santa_num].row][Santa[santa_num].col] = 0;
			Map[next_r][next_c] = santa_num;
			Santa[santa_num].row = next_r;
			Santa[santa_num].col = next_c;
			break;
		}
		else {
			int next_santa_num = Map[next_r][next_c];
			Map[Santa[santa_num].row][Santa[santa_num].col] = 0;
			Map[next_r][next_c] = santa_num;
			Santa[santa_num].row = next_r;
			Santa[santa_num].col = next_c;
			santa_num = next_santa_num;
		}
	}
}

int reverseDir(int dir) {
	if (dir == 0) {
		return 2;
	}
	else if (dir == 1) {
		return 3;
	}
	else if (dir == 2) {
		return 0;
	}
	else if (dir == 3) {
		return 1;
	}
	else if (dir == 4) {
		return 7;
	}
	else if (dir == 5) {
		return 6;
	}
	else if (dir == 6) {
		return 5;
	}
	else if (dir == 7) {
		return 4;
	}
}

void moveRudolf() {
	priority_queue<candi> pq_s;  //산타 후보군
	//1) 탈락하지 않은 산타
	//2) 제일 가까운 산타
	for (int i = 1; i <= P; i++) {
		if (!Santa[i].valid) continue;
		int dist = (Santa[i].row - RD_r) * (Santa[i].row - RD_r) + (Santa[i].col - RD_c) * (Santa[i].col - RD_c);
		pq_s.push({ Santa[i], dist });
	}

	candi target = pq_s.top();

	//2. 루돌프의 움직임 (상하좌우 대각선 8방향)
	//우선 순위 : 거리 작을수록 -> r좌표 클수록 -> c좌표 클수록
	priority_queue<selection> pq_dir; //방향 후보군
	
	for (int i = 0; i < 8; i++) {
		int next_r = RD_r + dr[i];
		int next_c = RD_c + dc[i];
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
		int dist = (target.s.row - next_r) * (target.s.row - next_r) + (target.s.col - next_c) * (target.s.col - next_c);
		pq_dir.push({ dist,i });
	}
	//향해서 돌진 
	RD_dir = pq_dir.top().dir;
	RD_r = RD_r + dr[RD_dir];
	RD_c = RD_c + dc[RD_dir];

	//충돌 : 산타와 루돌프 같은 칸 
	//1) 루돌프가 이동해서 박았을 때 : 산타 (루돌프 방향)으로 C칸 만큼
	if (Map[RD_r][RD_c] != 0) {
		if (Santa[Map[RD_r][RD_c]].valid) {
			Santa[Map[RD_r][RD_c]].score += C;
			Collision(reverseDir(RD_dir), C);  //날라온 방향, C
		}
		
	}
	
}

void moveSanta() {
	//3. 산타의 움직임
	
	//1번부터 P번까지 순서대로
	for (int i = 1; i <= P; i++) {
		//기절(기절시간 --) 했거나 탈락한 산타 무시
		if (!Santa[i].valid) continue;
		if (Santa[i].stun !=0) {
			continue;
		}
		//루돌프에게 가까워지는 방향으로 1칸 이동 (상우하좌 순위) -> 기존 거리 계산
		int prevDist = (Santa[i].row - RD_r) * (Santa[i].row - RD_r) + (Santa[i].col - RD_c) * (Santa[i].col - RD_c);
		priority_queue<selection> pq;
		
		for (int j = 0; j < 4; j++) {
			int next_r = Santa[i].row + dr[j];
			int next_c = Santa[i].col + dc[j];
			if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
			//1) 다른산타(탈락 아닌애들)랑 겹치는 칸 X
			if (Map[next_r][next_c] != 0) continue;
			int nextDist = (RD_r - next_r) * (RD_r - next_r) + (RD_c - next_c) * (RD_c - next_c);
			if (nextDist >= prevDist) continue;
			pq.push({ nextDist, j });
		}
		//2) 움직일 수 있는 칸 X (가만히)
		//3) 있더라도 루돌프 가까워지는 방향 없으면 (가만히)
		if (pq.empty()) continue;
		int nextDir = pq.top().dir;
		Map[Santa[i].row][Santa[i].col] = 0;
		Santa[i].row += dr[nextDir];
		Santa[i].col += dc[nextDir];
		Map[Santa[i].row][Santa[i].col]=i; 

		if (Santa[i].row == RD_r && Santa[i].col == RD_c) {
			Santa[i].score += D;
			Collision(nextDir, D);
		}

	}
	
}



void input() {
	//N: 게임판의 크기 (3≤N≤50)
	//M: 게임 턴 수(1≤M≤3000)
	//P: 산타의 수 (1≤P≤1000)
	//C: 루돌프의 힘 (1≤C≤N)
	//D: 산타의 힘 (1≤D≤N)
	cin >> N >> M >> P >> C >> D;

	cin >> RD_r >> RD_c;

	for (int i = 0; i < P; i++) {
		int id, r, c;
		cin >> id >> r >> c; //산타 번호, row, col
		Santa[id] = { r,c,0,0,true };
		Map[r][c] = id;
	}
}

void solution() {

	for (int i = 0; i < M; i++) {

		moveRudolf();
		moveSanta();

		//7. 종료
		//1) M번 턴 종료
		//2) 산타 모두 탈락
		bool allDone = true;
		for (int i = 1; i <= P; i++) {
			if (Santa[i].valid) {
				allDone = false;
				if (Santa[i].stun !=0 ) {
					Santa[i].stun--;
				}
				Santa[i].score += 1;
			}
		}
		if (allDone) break;
		//3) 매턴 이후 탈락 안한 산타 1점씩 부여
	}

}

void print() {
	int sum = 0;
	for (int i = 1; i <= P; i++) {
		cout << Santa[i].score << " ";
	}
	cout << "\n";
	
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	input();
	solution();
	print();

	return 0;
}



void gogo() {
	int santa_num = Map[RD_r][RD_c];
	if (!Santa[santa_num].valid) return;
	int rDir = reverseDir(RD_dir);
	while (1) {
		//While문 사용
		int next_r, next_c;
		if (Map[RD_r][RD_c] == santa_num) {
			//루돌프 박은 후 C만큼 날라간 뒤 기절
			Santa[santa_num].stun = 1;
			next_r = Santa[santa_num].row + C * dr[rDir];
			next_c = Santa[santa_num].col + C * dc[rDir];
		}
		else {
			next_r = Santa[santa_num].row + dr[rDir];
			next_c = Santa[santa_num].col + dc[rDir];
		}

		//break조건  
		//1) 밖으로 날아간 경우(탈락)
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) {
			Santa[santa_num].valid = false;
			break;
		}
		//2) 산타없는 경우
		if (Map[next_r][next_c] == 0) {
			Map[Santa[santa_num].row][Santa[santa_num].col] = 0;
			Map[next_r][next_c] = santa_num;
			Santa[santa_num].row = next_r;
			Santa[santa_num].col = next_c;
			break;
		}
		else {
			int next_santa_num = Map[next_r][next_c];
			Map[Santa[santa_num].row][Santa[santa_num].col] = 0;
			Map[next_r][next_c] = santa_num;
			Santa[santa_num].row = next_r;
			Santa[santa_num].col = next_c;
			santa_num = next_santa_num;
		}
	}
}


//문제 분석

//1. 게임판의 구성
//N x N 크기의 격자
//(1,1) 부터 (r,c)
//게임은 M개의 턴에 걸쳐 진행(루돌프(한번 움직인 뒤), 산타(P명) 한번씩 움직임)
// 칸 사이의 거리 : (r1-r2)^2 + (c1-c2)^2 (int 안넘음)


//2. 루돌프의 움직임 (상하좌우 대각선 8방향)
//1) 탈락하지 않은 산타
//2) 제일 가까운 산타
//향해서 돌진 
//우선 순위 : 거리 작을수록 -> r좌표 클수록 -> c좌표 클수록
//대각선도 1칸으로 취급 (??? : 거리는 다른데)

//3. 산타의 움직임
//1번부터 P번까지 순서대로
//기절(기절시간 --) 했거나 탈락한 산타 무시
//루돌프에게 가까워지는 방향으로 1칸 이동 (상우하좌 순위) -> 기존 거리 계산
//1) 다른산타(탈락 아닌애들)랑 겹치는 칸 X 
//2) 움직일 수 있는 칸 X (가만히)
//3) 있더라도 루돌프 가까워지는 방향 없으면 (가만히)

//4. 충돌
//충돌 : 산타와 루돌프 같은 칸 
//충돌 시 밀려남
//1) 루돌프가 이동해서 박았을 때 : 산타 (루돌프 방향)으로 C칸 만큼
//2) 산타가 움직여서 루돌프 박았을 때 : D만큼 점수 얻음 + 산타 자기방향 반대로 D칸
//이동하는 도중 충돌 X
//탈락 : 게임판 밖
//밀려난 칸에 산타있으면 상호작용


//5. 상호작용
//기존에 있던 산타 (날아온 산타방향 1칸) -> 연쇄적
//While문 사용
//break조건 : 1) 밖으로 날아간 경우 2) 산타없는 경우(탈락)

//6. 기절(k)
//루돌프와 충돌 후 기절 (다음턴(k+1)까지 기절)  1로 설정
//k+2부터 활성화
//기절하면 못움직임
//루돌프는 돌진 할 수 있음


//7. 종료
//1) M번 턴 종료
//2) 산타 모두 탈락
//3) 매턴 이후 탈락 안한 산타 1점씩 부여