#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

//���� �� �ִ� ����
//���� �����϶�
//(100000+100000) * K(100) * Q(4000) = 80,000,000,000 -> 800��
//��� ���� ��
//S(1000000) * Q(4000) = 4,000,000,000  -> 40��

//������ long int�� ����ؾ���

struct pos {
	//4���� ��ġ �켱����
	//1. ��+�� ū ĭ
	//2. �� ū ĭ
	//3. �� ū ĭ
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

	//�䳢�� ����
	//1. ���� ��ȣ pid
	//2. �ʼ� �̵��Ÿ� d

	int Pid;   //������ȣ
	int dist;  //�̵��Ÿ�
	int index; //�迭 �ε���
};

struct Jump {
	//���� ���� �켱���� ����
	//1. ������� ���� Ƚ�� ���� �䳢
	//2. ���� ���ִ� ĭ (��+��) ���� �䳢
	//3. �� ��ȣ ���� �䳢
	//4. �� ��ȣ ���� �䳢
	//5. ������ȣ ���� �䳢

	int jumpCnt;  //���� Ƚ��
	int row;
	int col;
	long score; //����
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

	//K�� �� ������ ��  (K���� �ϵ��� �ѹ��̶� ���� �䳢�� ���ؼ���)
	//  -> �����ߴ��� �迭 �����(participated)
	//���� S ���ϴ� �켱���� 
	//1. ���� ���ִ� ĭ (��+��) ū �䳢
	//2. �� ��ȣ ū �䳢
	//3. �� ��ȣ ū �䳢
	//5. ������ȣ ū �䳢

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

//P���� �䳢 (������: (1,1)) -> NxM ��� 1,1����
int Q;
int N, M, P;

Jump rabbitDAT[2000];  //�䳢�� DAT
bool Jumped[2000] = { false, };  //�پ����� Ȯ�� �迭

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

	//����
	//i�� �䳢�� d��ŭ �����¿�
	//ĭ ����� ������ �ݴ�� �ٲ� -> ���� �ٶ󺸴� dir �����س�����
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
		//�������� �� i�� �䳢 ���� ������ +=(��+��) ���� ����
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
		if (cmd == 100) {  //�Է�
			cin >> N >> M >> P;
			for (int j = 0; j < P; j++) {
				int id, dist;
				cin >> id >> dist;
				Jump temp = { 0,1,1,0, {id, dist, j} };
				rabbitDAT[j] = temp;
			}
		}
		else if (cmd == 200) { //����
			int K, S;
			cin >> K >> S;
			init(); //Jumped �迭 �ʱ�ȭ
			racestart(K, S);
		}
		else if (cmd == 300) { //�Ÿ� ����
			int id, L;
			cin >> id >> L;
			for (int i = 0; i < P; i++) {
				if (rabbitDAT[i].info.Pid == id) {
					rabbitDAT[i].info.dist *= L;
					break;
				}
			}
		}
		else if (cmd == 400) { //���� ���
			
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

//�䳢������ȣ�� �ʹ� ũ�Ƿ� ����ü�� ������ȣ �ְ� �׳� �迭[2000]�� �ؾ��ҵ�
//�۶����� �켱���� üũ�ؾ���



// �̵��Ÿ� ����
// Ư�� ������ȣ t�� ���� �̵��Ÿ� L�� �ϱ� (10�� �ȳ����ϱ� ����)


// ���� ���� �� ���� ���� ���� ��� (���ָ��� �ʱ�ȭ �ȵ�)