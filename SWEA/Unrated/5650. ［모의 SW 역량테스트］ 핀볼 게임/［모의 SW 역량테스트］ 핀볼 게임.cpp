#include <iostream>
#include<algorithm>

using namespace std;

const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };

const int dir[6][4] = {
    {0,1,2,3},  //빈칸
    {-1,3,0,-1}, //1번
    {3,-1,1,-1}, //2번
    {2,-1,-1,1}, //3번
    {-1,2,-1,0}, //4번
    {-1,-1,-1,-1}//5번
};
int N;
int Map[110][110] = { 0, };
pair<int, int> Wormhole[11][2];



//초기화 함수
void init() {
    for (int i = 0; i < 110; i++) {
        for (int j = 0; j < 110; j++) {
            Map[i][j] = 5;  //모든 것이 벽이다
        }
    }
}

//입력받는 함수
void input() {
    cin >> N;
    int wormHoleCnt[11] = { 0, }; //웜홀 몇번째 찾은건지?

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> Map[i][j];

            if (Map[i][j] >= 6 && Map[i][j] <= 10) { //웜홀인 경우
                int cnt = wormHoleCnt[Map[i][j]];
                Wormhole[Map[i][j]][cnt] = { i, j };
                wormHoleCnt[Map[i][j]]++;
            }
        }
    }

    int debugging = -1;
}

int Simulation(int row, int col, int d) { //공 실제 던지기
    //row,col에서 d라는 방향으로 공을 던졌을 때 시나리오

    int score = 0;

    int nowRow = row, nowCol = col, nowDir = d;
    //현재 위치 및 진행방향
    while (1) {
        //현재 진행 방향대로 움직이기
        nowRow += dr[nowDir];
        nowCol += dc[nowDir];

        int nowNum = Map[nowRow][nowCol];

        //움직이면서 직면할 상황 3 ~ 4가지
        
        // 1. 블랙홀 만날 경우 (끝)
        if (nowNum == -1) return score;

        // 2. 시작좌표 만날 경우 (끝)
        if (nowRow == row && nowCol == col) return score;

        // 3. 웜홀 만나는 경우
        if (nowNum >= 6) {
            auto A = Wormhole[nowNum][0];
            auto B = Wormhole[nowNum][1];
            pair<int, int> now = { nowRow,nowCol };
            if (A == now) {
                nowRow = B.first;
                nowCol = B.second;
            }
            else if (B == now) {
                nowRow = A.first;
                nowCol = A.second;
            }
        }

        // 4. 블록이거나 빈칸
        else {
            nowDir = dir[nowNum][nowDir];  //다음 방향 찾기

            //하지만 평평한 면을 만났다?
            if (nowDir == -1) {
                return score * 2 + 1;
            }

            if (nowNum >= 1) {
                score++;
            }
        }
        
    }

}


//Solution 함수
int solution() {

    int maxScore = 0;

    for (int row = 1; row <= N; row++) {
        for (int col = 1; col <= N; col++) {

            if (Map[row][col]) continue;

            for (int d = 0; d < 4; d++) {
                maxScore = max(maxScore, Simulation(row, col, d));
            }

        }
    }
    return maxScore;
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //freopen_s(new FILE*, "input.txt", "r", stdin);

    int T;
    cin >> T;

    for (int test = 1; test <= T; test++) {

        init();
        input();
        cout << "#" << test << " " << solution() << "\n";
    }

    return 0;
}