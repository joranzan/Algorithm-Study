#include <iostream>

using namespace std;

//상하좌우
//0 1 2 3
const int dr[4] = { -1,1,0,0 };
const int dc[4] = { 0,0,-1,1 };
int H, W;
int N;
char Map[21][21];
string s;



void Bullet(int row, int col, int dir) {

    //시작 위치 전차
    int nowRow = row;
    int nowCol = col;

    while (1) {

        nowRow += dr[dir];
        nowCol += dc[dir];

        //dir방향으로 직진

        //1. Map 벗어나면 끝
        if (nowRow < 0 || nowCol < 0 || nowRow >= H || nowCol >= W) return;

        //2. 강철 벽 만나면 소멸
        if (Map[nowRow][nowCol] == '#') return;

        //3. 벽돌 벽 만나면 벽돌 평지(.)로 바뀜
        if (Map[nowRow][nowCol] == '*') {
            Map[nowRow][nowCol] = '.';
        }
        

    }
    

}
//(row,col) 초기 전자 위치   dir: 초기 전차 방향
void Solution(int row, int col, int dir) {

    

}

int main()
{
    cin >> H >> W;
    int initial_dir = 0;
    int initial_r = 0;
    int initial_c = 0;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> Map[i][j];
            
            if (Map[i][j] == '^') {
                initial_dir = 0;
                initial_r = i;
                initial_c = j;
            }
            else if (Map[i][j] == 'v') {
                initial_dir = 1;
                initial_r = i;
                initial_c = j;
            }
            else if (Map[i][j] == '<') {
                initial_dir = 2;
                initial_r = i;
                initial_c = j;
            }
            else if (Map[i][j] == '>') {
                initial_dir = 3;
                initial_r = i;
                initial_c = j;
            }
        }
    }

    cin >> N;
    cin >> s;


    Solution(initial_r, initial_c, initial);

    return 0;
}



//맵의 정보
//  . : 평지(전차가 들어갈 수 있다.)
//  * : 벽돌로 만들어진 벽
//  # :	강철로 만들어진 벽
//  - : 물(전차는 들어갈 수 없다.)
//  ^ : 위쪽을 바라보는 전차(아래는 평지이다.)
//  v :	아래쪽을 바라보는 전차(아래는 평지이다.)
//  < : 왼쪽을 바라보는 전차(아래는 평지이다.)
//  > : 오른쪽을 바라보는 전차(아래는 평지이다.)


//문자	동작
//  U	Up : dir(상)으로 바꾸고, 한 칸 위의 칸이 평지라면 위 그 칸으로 이동한다.
//  D	Down : dir(하)으로 바꾸고, 한 칸 아래의 칸이 평지라면 그 칸으로 이동한다.
//  L	Left : dir(좌)으로 바꾸고, 한 칸 왼쪽의 칸이 평지라면 그 칸으로 이동한다.
//  R	Right : dir(우)으로 바꾸고, 한 칸 오른쪽의 칸이 평지라면 그 칸으로 이동한다.
//  S	Shoot : dir방향으로 포탄을 발사한다.


//포탄 동작
//벽돌(*)에 부딪히면 포탄 소멸 , 벽돌칸은 평지(.)
//강철(#)에 부딪히면 포탄 소멸,  아무일도 없음
//맵 밖에 나가면 포탄 소멸