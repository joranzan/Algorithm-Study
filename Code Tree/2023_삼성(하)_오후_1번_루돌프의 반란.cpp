//���� �ð� : 18:35
//���� �ð� : 
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

/*
�Է� ����

N : ���� ũ�� (3~50)
M : ���� ���� �� (1~1000)
P : ��Ÿ�� �� (1 ~ 30)
C : �絹���� ��
D : ��Ÿ�� ��
Pn : ��Ÿ�� ��ȣ (1~P)

*/

const int dr[8] = { -1,1,0,0,-1,-1,1,1 };
const int dc[8] = { 0,0,-1,1,-1,1,-1,1 };

//�������
const int dr_s[4] = { -1,0,1,0 };
const int dc_s[4] = { 0,1,0,-1 };
const int rv_dir[4] = { 2,3,0,1 };


struct pos {
	int row;
	int col;
};

struct rudolph {
	pos nowPos; //���� ��ġ
	int dir;    //�絹���� ����
};

struct santa {
	int id;
	pos nowPos;
	int dir;
	int stunned = 0;  //1�̸� ���� , 0�̸� Ȱ��ȭ
	bool alive = true;
	int score = 0;
};

int N, M, P, C, D;
santa SantaInfo[31];  //�� ��Ÿ�� ���� 
int SantaMap[51][51]; //��Ÿ�� ��ġ ����
rudolph RudolphInfo;

void init() {
	
	cin >> N >> M >> P >> C >> D;

	//SantaMap �ʱ�ȭ
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			SantaMap[r][c] = 0;
		}
	}

	//�絹�� ���� �ʱ�ȭ
	cin >> RudolphInfo.nowPos.row >> RudolphInfo.nowPos.col;
	RudolphInfo.dir = -1;

	for (int i = 1; i <= P; i++) {
		int id, r, c;
		cin >> id >> r >> c;
		//SantaMap �ʱ�ȭ
		SantaMap[r][c] = id;

		//SantaInfo �ʱ�ȭ
		SantaInfo[id].id = id;
		SantaInfo[id].nowPos.row = r;
		SantaInfo[id].nowPos.col = c;
		SantaInfo[id].dir = -1;
		SantaInfo[id].stunned = 0;
		SantaInfo[id].alive = true;
		SantaInfo[id].score = 0;
	}
}


void Interaction(int SantaID) {
	//4. ��ȣ�ۿ�

	//	1) ���� : �絹���� �浹 �� ���� �ڸ��� �ٸ� ��Ÿ �ִ� ���
	//	2) ���� �ִ� ��Ÿ�� �ش� �������� 1ĭ �з���(����)
	//	3) ���̻� ���� ��ġ�� ��Ÿ�� ���ٸ� ��
	//	4) ���ڹ����� �����ٸ� Ż��
	

	//��ȣ�ۿ� ������
	int nowRow = SantaInfo[SantaID].nowPos.row;
	int nowCol = SantaInfo[SantaID].nowPos.col;
	int nowDir = SantaInfo[SantaID].dir;
	int nowSantaID = SantaID;

	while (1) {
		//cout <<nowSantaID<<"�� ��Ÿ ����ͼ� ��ȣ�ۿ�!" << "\n";
		int nextSantaID = SantaMap[nowRow][nowCol];
		//cout << nextSantaID << "�� ��Ÿ ������ �־��µ� ���� �غ�!" << "\n";
		SantaMap[nowRow][nowCol] = nowSantaID;   //����� ��Ÿ�� ����

		int nextSantaRow = SantaInfo[nextSantaID].nowPos.row + dr[nowDir];
		int nextSantaCol = SantaInfo[nextSantaID].nowPos.col + dc[nowDir];

		//��ȣ�ۿ� �� �絹�� ���� �� ���� --> �׻� �ݴ�����̹Ƿ�

		if (nextSantaRow <= 0 || nextSantaCol <= 0 || nextSantaRow > N || nextSantaCol > N) {
			SantaInfo[nextSantaID].alive = false;
			//cout <<nextSantaID<< "�� ��Ÿ �׾ ��ȣ�ۿ� ��!\n";
			break;
		}


		//���� �������� ��Ÿ�ִٸ�
		if (SantaMap[nextSantaRow][nextSantaCol] != 0) {
			SantaInfo[nextSantaID].nowPos.row = nextSantaRow;
			SantaInfo[nextSantaID].nowPos.col = nextSantaCol;
			SantaInfo[nextSantaID].dir = nowDir;
			nowRow = nextSantaRow;
			nowCol = nextSantaCol;
			nowSantaID = nextSantaID;

		}
		else {
			SantaInfo[nextSantaID].nowPos.row = nextSantaRow;
			SantaInfo[nextSantaID].nowPos.col = nextSantaCol;
			SantaInfo[nextSantaID].dir = nowDir;
			SantaMap[nextSantaRow][nextSantaCol] = nextSantaID;
			//cout << "��ȣ�ۿ� ��!\n";
			break;
		}

	}

	//cout << "\n";

}


void moveRudolph() {

	int nowRow = RudolphInfo.nowPos.row;
	int nowCol = RudolphInfo.nowPos.col;

	

	//1. �絹�� ������

	//	1) ���� ����� ��Ÿ�� ���� 1ĭ ����
	//	1) �̵����� : �����¿�, �밢��
	//	2) 8���� �� ���� ��������� �������� �� ĭ ����
	//	2) �ִܰŸ� ������ ��
	//	2 - 1) r��ǥ�� ū ��Ÿ(�� �ؿ� �ִ� ��Ÿ)
	//	2 - 2) ������ �� : c��ǥ�� ū ��Ÿ(�� �����ʿ� �ִ� ��Ÿ)

	//*****************************************************
	//���� �絹���� ��ġ���� �ִܰŸ��� ��Ÿ ã�� 

	int targetSantaID = 2112345678;   //���� ����� ��Ÿ ID
	int minDist = 2112345678;
	


	//���� ã��
	for (int i = 1; i <= P; i++) {
		//1) Ż���� ��Ÿ ����
		if (!SantaInfo[i].alive) continue;
		int santaRow = SantaInfo[i].nowPos.row;
		int santaCol = SantaInfo[i].nowPos.col;
		int nowDist = pow(santaRow - nowRow, 2) + pow(santaCol - nowCol, 2);
		if (minDist < nowDist) continue;

		if (targetSantaID == 2112345678) {
			targetSantaID = i;
			minDist = nowDist;
			continue;
		}
		if (nowDist == minDist) {
			if (santaRow > SantaInfo[targetSantaID].nowPos.row) {
				targetSantaID = i;
				minDist = nowDist;
			}
			else if (santaRow == SantaInfo[targetSantaID].nowPos.row) {
				if (santaCol > SantaInfo[targetSantaID].nowPos.col) {
					targetSantaID = i;
					minDist = nowDist;
				}
			}
		}
		else {
			targetSantaID = i;
			minDist = nowDist;
		}
	}


	if (targetSantaID == 2112345678 || minDist == 2112345678) {
		return;
	}
	
	int RudolphDir = -1;

	int targetRow = SantaInfo[targetSantaID].nowPos.row;
	int targetCol = SantaInfo[targetSantaID].nowPos.col;
	int nowDist = 2112345678;
	//	2) 8���� �� ���� ��������� �������� �� ĭ ����
	for (int dir = 0; dir < 8; dir++) {
		int nextRow = nowRow + dr[dir];
		int nextCol = nowCol + dc[dir];
		if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
		int nextDist = pow(targetRow - nextRow, 2) + pow(targetCol - nextCol, 2);
		//���� ��������� �������� ����
		if (nextDist > minDist) continue;
		if (nextDist >= nowDist) continue;
		//������ ã�� ��Ÿ�� �Ÿ����� ũ�� ����
		
		nowDist = nextDist;
		RudolphDir = dir;
	}

	

	//�絹�� �̵�
	RudolphInfo.dir = RudolphDir;
	RudolphInfo.nowPos.row = nowRow + dr[RudolphDir];
	RudolphInfo.nowPos.col = nowCol + dc[RudolphDir];


	//�浹 ���� �Ǻ�
	int RudolphRow = RudolphInfo.nowPos.row;
	int RudolphCol = RudolphInfo.nowPos.col;

	//3. �浹
	//	1) ��Ÿ�� �絹�� ���� ĭ
	if (SantaMap[RudolphRow][RudolphCol] != 0) {
		
		int SantaID = SantaMap[RudolphRow][RudolphCol];
		int nowSantaRow = SantaInfo[SantaID].nowPos.row;
		int nowSantaCol = SantaInfo[SantaID].nowPos.col;
		int nextSantaRow = nowSantaRow + dr[RudolphDir] * C;
		int nextSantaCol = nowSantaCol + dc[RudolphDir] * C;

		//cout << SantaID << "�� ��Ÿ�� �浹! \n";
		//���� ĭ�� ��Ÿ ���ֱ�
		SantaMap[nowSantaRow][nowSantaCol] = 0;
		SantaInfo[SantaID].score += C;//��Ÿ�� C��ŭ ���� ����
		
		//���� �� ��� ���
		if (nextSantaRow <= 0 || nextSantaCol <= 0 || nextSantaRow > N || nextSantaCol > N) {
			SantaInfo[SantaID].alive = false;
		}
		//���� �� �ȹ�� ���
		else {
			//��Ÿ ���� ����
			SantaInfo[SantaID].dir = RudolphDir;
			SantaInfo[SantaID].nowPos.row = nextSantaRow;
			SantaInfo[SantaID].nowPos.col = nextSantaCol;
			SantaInfo[SantaID].stunned = 2;

			//���� ��ġ�� ��Ÿ�� �����Ѵٸ�
			if (SantaMap[nextSantaRow][nextSantaCol] != 0) {
				Interaction(SantaID);
			}
			else {
				SantaMap[nextSantaRow][nextSantaCol] = SantaID;
			}
		}

	}
	//	1 - 1) �絹���� �������� �浹 ���
	//	1) ��Ÿ�� C��ŭ ���� ����
	//	2) �絹���� �̵��� �������� Cĭ��ŭ �з���
			//2-1) �浹 ��� ������----->���󰡴� ���߿� �浹 ����
			//2-2) �з��� ��ġ�� ���� �� : Ż��
			//2-3) �з��� ĭ�� �ٸ� ��Ÿ : ��ȣ�ۿ� �߻�


	//5. ����

	//	1) ���� : ��Ÿ�� �絹���� �浹 �� ����
	//	2) k��° �Ͽ� ����---- > k + 1�� ���� ���� ����
	//	3) k + 2��° �Ͽ��� �������
	//	4)************** ���� ���¿��� �浹, ��ȣ�ۿ� ����!!!!!
	//	5)************** �絹���� ������ ��Ÿ�� ���� ������� ���� ����!!
}

void moveSanta() {

	//2. ��Ÿ�� ������

	//	1) 1������ P������ ������� ������
	//	1 - 1) ������ ��Ÿ ����
	//	1 - 2) Ż���� ��Ÿ ����
	//	2) �絹���� ���� ��������� �������� �̵�
	//	2 - 1) �����¿� 4����
	//	2 - 2) �켱���� : �����¿�
	//	2 - 3) ���� �� ����
	//	2 - 4) �ٸ� ��Ÿ �ִٸ� ����
	//	2 - 5) ���� ���ٸ� �������� ����
	//	2 - 6) ������ �� �־ ��������� ������ ����

	for (int i = 1; i <= P; i++) {
		if (!SantaInfo[i].alive) continue;  //Ż���� ��Ÿ ����
		if (SantaInfo[i].stunned!=0) {      //������ ��Ÿ ����
			SantaInfo[i].stunned--;
			continue;
		}

		int nowRow = SantaInfo[i].nowPos.row;
		int nowCol = SantaInfo[i].nowPos.col;
		int nowDist = pow(nowRow - RudolphInfo.nowPos.row, 2) + pow(nowCol - RudolphInfo.nowPos.col, 2);
		int minDist = 2112345678;
		int minDir = -1;
		
		for (int dir = 0; dir < 4; dir++) {
			int nextRow = nowRow + dr_s[dir];
			int nextCol = nowCol + dc_s[dir];
			if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) continue;
			if (SantaMap[nextRow][nextCol] != 0) continue;
			int nextDist = pow(nextRow - RudolphInfo.nowPos.row, 2) + pow(nextCol - RudolphInfo.nowPos.col, 2);
			if (nextDist >= nowDist) continue;

			if (nextDist < minDist) {
				minDir = dir;
				minDist = nextDist;
			}
		}

		if (minDir == -1) continue;

		int nextRow = nowRow + dr_s[minDir];
		int nextCol = nowCol + dc_s[minDir];

		//�̵��� �� �ִ� ĭ ����
		SantaMap[nowRow][nowCol] = 0; //���� ĭ ����
		//���� �絹���� �����Ѵٸ� 
		if (RudolphInfo.nowPos.row == nextRow && RudolphInfo.nowPos.col == nextCol) {
			

			SantaInfo[i].score += D;    //��Ÿ�� D��ŭ ���� ����
			//cout << i << "�� ��Ÿ �̵� �� �絹���� �浹!\n";
			//�ڽ��� �̵��� ����(�ݴ��) Dĭ��ŭ �̵�
			int nextNextRow = nextRow + dr_s[rv_dir[minDir]] * D;
			int nextNextCol = nextCol + dc_s[rv_dir[minDir]] * D;
			if (nextNextRow <= 0 || nextNextCol <= 0 || nextNextRow > N || nextNextCol > N) {
				SantaInfo[i].alive = false;
			}
			else {
				//�����¿�
				  //�������
				int DirMap[4] = { 0,3,1,2 };
				SantaInfo[i].dir = DirMap[rv_dir[minDir]];
				SantaInfo[i].nowPos.row = nextNextRow;
				SantaInfo[i].nowPos.col = nextNextCol;
				SantaInfo[i].stunned = 1;

				if (SantaMap[nextNextRow][nextNextCol] != 0) {
					Interaction(i);
				}
				else {
					SantaMap[nextNextRow][nextNextCol] = i;
				}
			}
		}
		//�絹�� ���ٸ�
		else {
			SantaMap[nextRow][nextCol] = i;
			SantaInfo[i].dir = minDir;
			SantaInfo[i].nowPos.row = nextRow;
			SantaInfo[i].nowPos.col = nextCol;
		}

	}


	//3. �浹
	//	1) ��Ÿ�� �絹�� ���� ĭ

	//	1-2) ��Ÿ�� �������� �浹 ���
	//	1) ��Ÿ�� D��ŭ ���� ����
	//	2) �ڽ��� �̵��� ����(�ݴ��) Dĭ��ŭ �̵�

	//	2) �浹 ��� ������----->���󰡴� ���߿� �浹 ����
	//	3) �з��� ��ġ�� ���� �� : Ż��
	//	4) �з��� ĭ�� �ٸ� ��Ÿ : ��ȣ�ۿ� �߻�



	//5. ����

	//	1) ���� : ��Ÿ�� �絹���� �浹 �� ����
	//	2) k��° �Ͽ� ����---- > k + 1�� ���� ���� ����
	//	3) k + 2��° �Ͽ��� �������
	//	4)************** ���� ���¿��� �浹, ��ȣ�ۿ� ����!!!!!
	//	5)************** �絹���� ������ ��Ÿ�� ���� ������� ���� ����!!
}

void solution() {

	for (int turn = 1; turn <= M; turn++) {

		//cout << "--------------------------------------------------------------------------\n";
		//cout << turn << "��° �� \n\n";

		//cout << "�̵� �� �絹���� ��ġ: (" << RudolphInfo.nowPos.row << " " << RudolphInfo.nowPos.col << ")\n\n";



		//cout << "�絹�� �̵� �� ��Ÿ���� ��ġ\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << SantaMap[r][c] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";

		//if (turn == 7) {
		//	int debug = -1;
		//}
		//�絹�� ������ (�浹 �� ��ȣ�ۿ� ����)
		moveRudolph();

		//cout << "�̵� �� �絹���� ��ġ: (" << RudolphInfo.nowPos.row << " " << RudolphInfo.nowPos.col << ")\n\n";


		//cout << "�絹�� �̵� �� ��Ÿ���� ��ġ\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << SantaMap[r][c] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";

		//��Ÿ ������ (�浹 �� ��ȣ�ۿ� ����)
		moveSanta();


		//cout << "��Ÿ �̵� �� ��Ÿ���� ��ġ\n";
		//for (int r = 1; r <= N; r++) {
		//	for (int c = 1; c <= N; c++) {
		//		cout << SantaMap[r][c] << " ";
		//	}
		//	cout << "\n";
		//}
		//cout << "\n";

		//6. ���� ����

		bool isDone = true;

		for (int i = 1; i <= P; i++) {
			if (!SantaInfo[i].alive) {
				//cout << "����(" << SantaInfo[i].score << ") ";
				continue;
			}
			isDone = false;
			SantaInfo[i].score++;
			//cout << SantaInfo[i].score << " ";
		}

		//cout << "\n";

		//	1) M���� ���� ������ ����
		//	2) ��Ÿ ��� Ż���̸� ����
		//	3) �� �ϸ��� Ż������ ���� ��Ÿ�鿡�� 1���� �ο�

		if (isDone) break;
	}

	for (int i = 1; i <= P; i++) {
		cout << SantaInfo[i].score << " ";
	}

}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	init();
	solution();

	return 0;
}

/*
���� �м�

��Ÿ : P�� 
�絹�� : ��Ÿ���� ��ġ�� �Ͽ� ��Ÿ�� ������ ����


���� ����

1. NxN (1,1) 
2. �� �� : M 

	1) �絹�� �ѹ� ������ 
	2) 1�� ~ P�� ��Ÿ���� ������� ������

3. �Ÿ� ��� (r����)^2 + (c����)^2


���� ����

1. �絹�� ������ 

	1) ���� ����� ��Ÿ�� ���� 1ĭ ���� 
		1) �̵����� : �����¿�, �밢�� 
		2) 8���� �� ���� ��������� �������� �� ĭ ���� 
	2) �ִܰŸ� ������ ��
		2-1) r��ǥ�� ū ��Ÿ (�� �ؿ� �ִ� ��Ÿ)
		2-2) ������ ��: c��ǥ�� ū ��Ÿ (�� �����ʿ� �ִ� ��Ÿ)
	
2. ��Ÿ�� ������

	1) 1������ P������ ������� ������
		1-1) ������ ��Ÿ ����
		1-2) Ż���� ��Ÿ ����
	2) �絹���� ���� ��������� �������� �̵�
		2-1) �����¿� 4����
		2-2) �켱���� : �������
		2-3) ���� �� ����
		2-4) �ٸ� ��Ÿ �ִٸ� ����
		2-5) ���� ���ٸ� �������� ����
		2-6) ������ �� �־ ��������� ������ ����
	
3. �浹 
	1) ��Ÿ�� �絹�� ���� ĭ

		1-1) �絹���� �������� �浹 ���
			1) ��Ÿ�� C��ŭ ���� ����
			2) �絹���� �̵��� �������� Cĭ��ŭ �з���
			

		1-2) ��Ÿ�� �������� �浹 ���
			1) ��Ÿ�� D��ŭ ���� ����
			2) �ڽ��� �̵��� ���� (�ݴ��) Dĭ��ŭ �̵�

	2) �浹 ��� ������ -----> ���󰡴� ���߿� �浹 ����
	3) �з��� ��ġ�� ���� �� : Ż��
	4) �з��� ĭ�� �ٸ� ��Ÿ : ��ȣ�ۿ� �߻�


4. ��ȣ�ۿ�

	1) ���� : �絹���� �浹 �� ���� �ڸ��� �ٸ� ��Ÿ �ִ� ���
	2) ���� �ִ� ��Ÿ�� �ش� �������� 1ĭ �з��� (����)
	3) ���̻� ���� ��ġ�� ��Ÿ�� ���ٸ� ��
	4) ���ڹ����� �����ٸ� Ż��


5. ���� 

	1) ���� : ��Ÿ�� �絹���� �浹 �� ����
	2) k��° �Ͽ� ���� ----> k+1�� ���� ���� ����
	3) k+2��° �Ͽ��� �������
	4) **************���� ���¿��� �浹, ��ȣ�ۿ� ����!!!!!
	5) **************�絹���� ������ ��Ÿ�� ���� ������� ���� ����!!


6. ���� ����

	1) M���� ���� ������ ����
	2) ��Ÿ ��� Ż���̸� ����
	3) �� �ϸ��� Ż������ ���� ��Ÿ�鿡�� 1���� �ο�



��ǥ : �� ��Ÿ�� ���� ���� ����
*/

/*
���� ó��

1. ��Ÿ ����
	1) ������ ��Ÿ
	2) ���� �ۿ� �������� Ż���� ��Ÿ

2. �絹���� ���� ���� �� 
	1) Ż���� ��Ÿ ����



*/