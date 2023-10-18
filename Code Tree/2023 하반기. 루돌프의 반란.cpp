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
//�밢���� 1ĭ���� ��� (??? : �Ÿ��� �ٸ���)
const int dr[8] = { -1,0,1,0,-1,1,-1,1 };
const int dc[8] = { 0,1,0,-1,-1,-1,1,1 };

//1. �������� ����
//N x N ũ���� ����
//(1,1) ���� (r,c)
//������ M���� �Ͽ� ���� ����(�絹��(�ѹ� ������ ��), ��Ÿ(P��) �ѹ��� ������)
// ĭ ������ �Ÿ� : (r1-r2)^2 + (c1-c2)^2 (int �ȳ���)

int Map[51][51];
int N, M, P, C, D;
int RD_r, RD_c;
int RD_dir;
santa Santa[1001];   //��Ÿ ���� �迭
int reverseDir(int dir);

void Collision(int dir, int num) {  //�浹
	
	int santa_num = Map[RD_r][RD_c];
	if (!Santa[santa_num].valid) return;
	int rDir = reverseDir(dir);
	while (1) {
		//While�� ���
		int next_r, next_c;
		if (Map[RD_r][RD_c] == santa_num) {
			//�絹�� ���� �� C��ŭ ���� �� ����
			Santa[santa_num].stun = 2;
			next_r = Santa[santa_num].row + num * dr[rDir];
			next_c = Santa[santa_num].col + num * dc[rDir];
		}
		else {
			next_r = Santa[santa_num].row + dr[rDir];
			next_c = Santa[santa_num].col + dc[rDir];
		}

		//break����  
		//1) ������ ���ư� ���(Ż��)
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) {
			Santa[santa_num].valid = false;
			break;
		}
		//2) ��Ÿ���� ���
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
	priority_queue<candi> pq_s;  //��Ÿ �ĺ���
	//1) Ż������ ���� ��Ÿ
	//2) ���� ����� ��Ÿ
	for (int i = 1; i <= P; i++) {
		if (!Santa[i].valid) continue;
		int dist = (Santa[i].row - RD_r) * (Santa[i].row - RD_r) + (Santa[i].col - RD_c) * (Santa[i].col - RD_c);
		pq_s.push({ Santa[i], dist });
	}

	candi target = pq_s.top();

	//2. �絹���� ������ (�����¿� �밢�� 8����)
	//�켱 ���� : �Ÿ� �������� -> r��ǥ Ŭ���� -> c��ǥ Ŭ����
	priority_queue<selection> pq_dir; //���� �ĺ���
	
	for (int i = 0; i < 8; i++) {
		int next_r = RD_r + dr[i];
		int next_c = RD_c + dc[i];
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
		int dist = (target.s.row - next_r) * (target.s.row - next_r) + (target.s.col - next_c) * (target.s.col - next_c);
		pq_dir.push({ dist,i });
	}
	//���ؼ� ���� 
	RD_dir = pq_dir.top().dir;
	RD_r = RD_r + dr[RD_dir];
	RD_c = RD_c + dc[RD_dir];

	//�浹 : ��Ÿ�� �絹�� ���� ĭ 
	//1) �絹���� �̵��ؼ� �ھ��� �� : ��Ÿ (�絹�� ����)���� Cĭ ��ŭ
	if (Map[RD_r][RD_c] != 0) {
		if (Santa[Map[RD_r][RD_c]].valid) {
			Santa[Map[RD_r][RD_c]].score += C;
			Collision(reverseDir(RD_dir), C);  //����� ����, C
		}
		
	}
	
}

void moveSanta() {
	//3. ��Ÿ�� ������
	
	//1������ P������ �������
	for (int i = 1; i <= P; i++) {
		//����(�����ð� --) �߰ų� Ż���� ��Ÿ ����
		if (!Santa[i].valid) continue;
		if (Santa[i].stun !=0) {
			continue;
		}
		//�絹������ ��������� �������� 1ĭ �̵� (������� ����) -> ���� �Ÿ� ���
		int prevDist = (Santa[i].row - RD_r) * (Santa[i].row - RD_r) + (Santa[i].col - RD_c) * (Santa[i].col - RD_c);
		priority_queue<selection> pq;
		
		for (int j = 0; j < 4; j++) {
			int next_r = Santa[i].row + dr[j];
			int next_c = Santa[i].col + dc[j];
			if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) continue;
			//1) �ٸ���Ÿ(Ż�� �ƴѾֵ�)�� ��ġ�� ĭ X
			if (Map[next_r][next_c] != 0) continue;
			int nextDist = (RD_r - next_r) * (RD_r - next_r) + (RD_c - next_c) * (RD_c - next_c);
			if (nextDist >= prevDist) continue;
			pq.push({ nextDist, j });
		}
		//2) ������ �� �ִ� ĭ X (������)
		//3) �ִ��� �絹�� ��������� ���� ������ (������)
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
	//N: �������� ũ�� (3��N��50)
	//M: ���� �� ��(1��M��3000)
	//P: ��Ÿ�� �� (1��P��1000)
	//C: �絹���� �� (1��C��N)
	//D: ��Ÿ�� �� (1��D��N)
	cin >> N >> M >> P >> C >> D;

	cin >> RD_r >> RD_c;

	for (int i = 0; i < P; i++) {
		int id, r, c;
		cin >> id >> r >> c; //��Ÿ ��ȣ, row, col
		Santa[id] = { r,c,0,0,true };
		Map[r][c] = id;
	}
}

void solution() {

	for (int i = 0; i < M; i++) {

		moveRudolf();
		moveSanta();

		//7. ����
		//1) M�� �� ����
		//2) ��Ÿ ��� Ż��
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
		//3) ���� ���� Ż�� ���� ��Ÿ 1���� �ο�
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
		//While�� ���
		int next_r, next_c;
		if (Map[RD_r][RD_c] == santa_num) {
			//�絹�� ���� �� C��ŭ ���� �� ����
			Santa[santa_num].stun = 1;
			next_r = Santa[santa_num].row + C * dr[rDir];
			next_c = Santa[santa_num].col + C * dc[rDir];
		}
		else {
			next_r = Santa[santa_num].row + dr[rDir];
			next_c = Santa[santa_num].col + dc[rDir];
		}

		//break����  
		//1) ������ ���ư� ���(Ż��)
		if (next_r <= 0 || next_c <= 0 || next_r > N || next_c > N) {
			Santa[santa_num].valid = false;
			break;
		}
		//2) ��Ÿ���� ���
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


//���� �м�

//1. �������� ����
//N x N ũ���� ����
//(1,1) ���� (r,c)
//������ M���� �Ͽ� ���� ����(�絹��(�ѹ� ������ ��), ��Ÿ(P��) �ѹ��� ������)
// ĭ ������ �Ÿ� : (r1-r2)^2 + (c1-c2)^2 (int �ȳ���)


//2. �絹���� ������ (�����¿� �밢�� 8����)
//1) Ż������ ���� ��Ÿ
//2) ���� ����� ��Ÿ
//���ؼ� ���� 
//�켱 ���� : �Ÿ� �������� -> r��ǥ Ŭ���� -> c��ǥ Ŭ����
//�밢���� 1ĭ���� ��� (??? : �Ÿ��� �ٸ���)

//3. ��Ÿ�� ������
//1������ P������ �������
//����(�����ð� --) �߰ų� Ż���� ��Ÿ ����
//�絹������ ��������� �������� 1ĭ �̵� (������� ����) -> ���� �Ÿ� ���
//1) �ٸ���Ÿ(Ż�� �ƴѾֵ�)�� ��ġ�� ĭ X 
//2) ������ �� �ִ� ĭ X (������)
//3) �ִ��� �絹�� ��������� ���� ������ (������)

//4. �浹
//�浹 : ��Ÿ�� �絹�� ���� ĭ 
//�浹 �� �з���
//1) �絹���� �̵��ؼ� �ھ��� �� : ��Ÿ (�絹�� ����)���� Cĭ ��ŭ
//2) ��Ÿ�� �������� �絹�� �ھ��� �� : D��ŭ ���� ���� + ��Ÿ �ڱ���� �ݴ�� Dĭ
//�̵��ϴ� ���� �浹 X
//Ż�� : ������ ��
//�з��� ĭ�� ��Ÿ������ ��ȣ�ۿ�


//5. ��ȣ�ۿ�
//������ �ִ� ��Ÿ (���ƿ� ��Ÿ���� 1ĭ) -> ������
//While�� ���
//break���� : 1) ������ ���ư� ��� 2) ��Ÿ���� ���(Ż��)

//6. ����(k)
//�絹���� �浹 �� ���� (������(k+1)���� ����)  1�� ����
//k+2���� Ȱ��ȭ
//�����ϸ� ��������
//�絹���� ���� �� �� ����


//7. ����
//1) M�� �� ����
//2) ��Ÿ ��� Ż��
//3) ���� ���� Ż�� ���� ��Ÿ 1���� �ο�