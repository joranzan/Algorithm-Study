#include<iostream>
#include<queue>

using namespace std;

/*
�Է�
N : ���� ũ��(20����)
M : �÷��̾� �� (30����)
K : ���� ��

x y d s (��ġ, ����, �ɷ�ġ)

�� ���ݷ� : 100000����

�ɷ�ġ : 100����

*/

const int dr[4] = { -1,0,1,0 };
const int dc[4] = { 0,1,0,-1 };

//�ݴ�������� �̵��� �� ���
const int dir_reverse[4] = { 2,3,0,1 };


struct pos {
    int row;
    int col;
};

struct player {
    pos nowPos;    //��ġ
    int playerId;  //�÷��̾� ��ȣ
    int initial_power;  //�ʱ� �ɷ�ġ
    int weapon = 0;     //���� ���ݷ�
    int dir;  // ����
    int score = 0;

    bool operator<(player next) const {
        if (initial_power + weapon < next.initial_power + next.weapon) return true;
        else if (initial_power + weapon > next.initial_power + next.weapon) return false;
        else {
            if (initial_power < next.initial_power) return true;
            else return false;
        }
    }

};

int N, M, K;
priority_queue<int> GunMap[21][21];
int PlayerMap[21][21] = { 0, };
player PlayerInfo[31];

void init() {
    cin >> N >> M >> K;

    //���� �Է� �ޱ�
    for (int r = 1; r <= N; r++) {
        for (int c = 1; c <= N; c++) {
            while (!GunMap[r][c].empty()) GunMap[r][c].pop();
            int temp;
            cin >> temp;
            if (temp == 0) continue;
            GunMap[r][c].push(temp);
        }
    }

    for (int i = 1; i <= M; i++) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        PlayerMap[x][y] = i;
        PlayerInfo[i].nowPos.row = x;
        PlayerInfo[i].nowPos.col = y;
        PlayerInfo[i].playerId = i;
        PlayerInfo[i].initial_power = s;
        PlayerInfo[i].dir = d;
    }

}

void loserProcess(int loserNum) {   


    int nowRow = PlayerInfo[loserNum].nowPos.row;
    int nowCol = PlayerInfo[loserNum].nowPos.col;
    int nowDir = PlayerInfo[loserNum].dir;
    int returnGun = PlayerInfo[loserNum].weapon;
    //1) �� ��������
    PlayerInfo[loserNum].weapon = 0;
    GunMap[nowRow][nowCol].push(returnGun);
    //2) �ٶ󺸴� �������� 1ĭ �̵�
    int nextRow = nowRow + dr[loserNum];
    int nextCol = nowCol + dc[loserNum];
    //  1) �ٸ� �÷��̾� ���� �Ǵ� ���� �� : �ð���� 90�� ȸ���Ͽ� ��ĭ ã�� �� �̵�
   
    for (int i = 0; i < 4; i++) {
            int nextDir = i + nowDir;
            nextDir %= 4;
            int tempRow = nowRow + dr[nextDir];
            int tempCol = nowCol + dc[nextDir];
            if (tempRow <= 0 || tempCol <= 0 || tempRow > N || tempCol > N || PlayerMap[tempRow][tempCol] != 0) continue;
            nextRow = tempRow;
            nextCol = tempCol;
            nowDir = nextDir;
            break;
    }
    

    //****���� �ȹٷ� ���ֱ�*****
    //PlayerInfo[playerNum]�� ���� ����
    PlayerInfo[loserNum].dir = nowDir;
    PlayerInfo[loserNum].nowPos.row = nextRow;
    PlayerInfo[loserNum].nowPos.col = nextCol;
    //PlayerMap ����
    PlayerMap[nowRow][nowCol] = 0;
    PlayerMap[nextRow][nextCol] = loserNum;
    
   
    //3) ���� ������ max �� ���� ��������
    if (!GunMap[nextRow][nextCol].empty()) {
        PlayerInfo[loserNum].weapon = GunMap[nextRow][nextCol].top();
        GunMap[nextRow][nextCol].pop();
    }



}

void winnerProcess(int winnerNum) {
    
    //1) �¸��� ĭ�� ������ max �� ȹ�� �� ������ ��������
    int nowRow = PlayerInfo[winnerNum].nowPos.row;
    int nowCol = PlayerInfo[winnerNum].nowPos.col;
    int nowWeapon = PlayerInfo[winnerNum].weapon;

    PlayerMap[nowRow][nowCol] = winnerNum;
    
    if (nowWeapon < GunMap[nowRow][nowCol].top()) {
        PlayerInfo[winnerNum].weapon = GunMap[nowRow][nowCol].top();
        GunMap[nowRow][nowCol].pop();
        GunMap[nowRow][nowCol].push(nowWeapon);
    }
}

void movePlayer(int playerNum) {

    int nowRow = PlayerInfo[playerNum].nowPos.row;
    int nowCol = PlayerInfo[playerNum].nowPos.col;
    int nowWeapon = PlayerInfo[playerNum].weapon;
    int nowDir = PlayerInfo[playerNum].dir;

    //1) ù��° �÷��̾���� ���������� 1ĭ (������ ���ϰ� �ִ� ��������)

    int nextRow = nowRow + dr[nowDir];
    int nextCol = nowCol + dc[nowDir];
    //(���� ����� �ݴ�������� 1ĭ �̵�)
    if (nextRow <= 0 || nextCol <= 0 || nextRow > N || nextCol > N) {
        nextRow = nowRow + dr[dir_reverse[nowDir]];
        nextCol = nowCol + dc[dir_reverse[nowDir]];
        nowDir = dir_reverse[nowDir];
    }

    //****���� �ȹٷ� ���ֱ�*****
    //PlayerInfo[playerNum]�� ���� ����
    PlayerInfo[playerNum].dir = nowDir;
    PlayerInfo[playerNum].nowPos.row = nextRow;
    PlayerInfo[playerNum].nowPos.col = nextCol;
    //PlayerMap ����
    PlayerMap[nowRow][nowCol] = 0;
    //GunMap ����

    //2-1) �̵��� ���⿡ �÷��̾ ���� ���
    if (PlayerMap[nextRow][nextCol] == 0) {

        //�ش� ĭ�� ���� �ִ� ���
        if (!GunMap[nextRow][nextCol].empty()) {
            //1) ���� ������ ���� �ʴ� ��� : �� ȹ��
            if (nowWeapon == 0) {
                PlayerInfo[playerNum].weapon = GunMap[nextRow][nextCol].top();
                GunMap[nextRow][nextCol].pop();
            }
            //2) ���� ������ �ִ� ��� : ���ݷ� max�� �� ���� ��������
            else {
                if (nowWeapon < GunMap[nextRow][nextCol].top()) {
                    PlayerInfo[playerNum].weapon = GunMap[nextRow][nextCol].top();
                    GunMap[nextRow][nextCol].pop();
                    GunMap[nextRow][nextCol].push(nowWeapon);
                }
            }
        }
        //�ش� ĭ�� ���� ���� ��� ��ġ�� ����
        PlayerMap[nowRow][nowCol] = 0;
        PlayerMap[nextRow][nextCol] = playerNum;
        

    }
    //2-2) �̵��� ���⿡ �÷��̾ �ִ� ��� ����
    else {
        int otherPlayerNum = PlayerMap[nextRow][nextCol];

        //1) �ʱ� �ɷ�ġ + ���� ���ݷ� ū �÷��̾ �¸�
        //2) ������ ��� : �ʱ� �ɷ�ġ�� �� ū �÷��̾ �¸�
        int winner = 0;
        int loser = 0;
        int score = abs(PlayerInfo[playerNum].initial_power + PlayerInfo[playerNum].weapon - PlayerInfo[otherPlayerNum].weapon - PlayerInfo[otherPlayerNum].initial_power);
        if (PlayerInfo[playerNum] < PlayerInfo[otherPlayerNum]) {
            winner = otherPlayerNum;
            loser = playerNum;
        }
        else{
            winner = playerNum;
            loser = otherPlayerNum;
        }


        //�� �÷��̾�
        loserProcess(loser);

        //�̱� �÷��̾�
        winnerProcess(winner);

        //3) ���� ȹ�� : �÷��̾� �� (�ʱ�ɷ�ġ + ���� ���ݷ� ����) ȹ��
        PlayerInfo[winner].score += score;
    }
}


void solution() {


    for (int k = 0; k < K; k++) {
        for (int p = 1; p <= M; p++) {
            movePlayer(p);
        }    
        
        //cout << "\n";
    }

    for (int p = 1; p <= M; p++) {
        cout << PlayerInfo[p].score << " ";
    }



}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    init();
    solution();

    return 0;
}


/*

�� ũ�� : NxN

���� ����

- ����
    - ���ݷ�
- �÷��̾� (���� ���� ��ġ)
    - �÷��̾� ��ȣ
    - �ʱ� �ɷ�ġ(��� �ٸ�)

���� ���� (��� �÷��̾ ������� �ϸ� 1���� ���� )

1) ù��° �÷��̾���� ���������� 1ĭ (������ ���ϰ� �ִ� ��������)
    (���� ����� �ݴ�������� 1ĭ �̵�)

2-1) �̵��� ���⿡ �÷��̾ ���� ���
     1) ���� ������ ���� �ʴ� ��� : �� ȹ�� (�ɷ�ġ ����)
     2) ���� ������ �ִ� ��� : ���ݷ� max�� �� ���� ��������

2-2) �̵��� ���⿡ �÷��̾ �ִ� ��� ����
    1) �ʱ� �ɷ�ġ + ���� ���ݷ� ū �÷��̾ �¸�
    2) ������ ��� : �ʱ� �ɷ�ġ�� �� ū �÷��̾ �¸�

    3) ���� ȹ�� : �÷��̾� �� (�ʱ�ɷ�ġ + ���� ���ݷ� ����) ȹ��


    - �� �÷��̾�
        1) �� ��������
        2) �ٶ󺸴� �������� 1ĭ �̵�
            1-1) �ٸ� �÷��̾� ���� �Ǵ� ���� �� : �ð���� 90�� ȸ���Ͽ� ��ĭ ã�� �� �̵�
        3) ���� ������ max �� ���� ��������


    - �̱� �÷��̾�
        1) �¸��� ĭ�� ������ max �� ȹ�� �� ������ ��������


****������ �÷��̾�� �����ؾ���******



**********************************
�Է�
N : ���� ũ��(20����)
M : �÷��̾� �� (30����)
K : ���� ��

x y d s (��ġ, ����, �ɷ�ġ)

�� ���ݷ� : 100000����

�ɷ�ġ : 100����

*/