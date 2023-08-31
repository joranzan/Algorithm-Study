#include <iostream>
#include<cmath>

using namespace std;


//4개의 자석  8개의 날  N S

// N:0점  S: ( 2^[자석번호-1] )점

//규칙
//자성이 다르면 반대방향 1칸
//자성이 같으면 그대로

int arr[5][8] = { 0, };
int check[5] = { 0 };

void Rotation();
void CW(int num);
void CCW(int num);

void turn_check(int start, int dir) {

    check[start] = dir;
    //왼쪽 체크
    for (int i = start - 1; i >= 1; i--) {

        int pivot1 = arr[i + 1][6];
        int pivot2 = arr[i][2];

        if (pivot1 != pivot2) {
            check[i] = check[i + 1] * (-1);
        }
        else break;
    }

    //오른쪽 체크
    for (int i = start + 1; i <= 4; i++) {
        
        int pivot1 = arr[i - 1][2];
        int pivot2 = arr[i][6];

        if (pivot1 != pivot2) {
            check[i] = check[i - 1] * (-1);
        }
        else break;
    }

    Rotation();
        
}

void Rotation() {

    for (int i = 1; i <= 4; i++) {

        int dir = check[i];
        if (dir == 0) continue;
        else if (dir == 1) {   //시계방향
            CW(i);
        }
        else if (dir == -1) {  //반시계방향
            CCW(i);
        }
    }


}

void CW(int num) {

    int temp = arr[num][7];

    for (int i = 7; i >= 1; i--) {
        arr[num][i] = arr[num][i - 1];
    }

    arr[num][0] = temp;

}

void CCW(int num) {

    int temp = arr[num][0];

    for (int i = 0; i < 7; i++) {
        arr[num][i] = arr[num][i + 1];
    }

    arr[num][7] = temp;

}

int Calculate() {

    int ret = 0;

    for (int i = 1; i <= 4; i++) {
        int polar = arr[i][0];
        if (polar == 1) {
            ret += pow(2, i - 1);
        }
    }

    return ret;
}



int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    //freopen_s(new FILE*, "input.txt", "r", stdin);


    int T;
    cin >> T;

    for (int test = 1; test <= T; test++) {

        int Q;
        cin >> Q;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> arr[i][j];
            }
        }

        for (int i = 0; i < Q; i++) {
            //자석의 번호,    회전방향(시계:1, 반시계: -1)
            int num, dir;
            cin >> num >> dir;
            for (int i = 1; i <= 4; i++) {
                check[i] = 0;
            }

            turn_check(num, dir);

        }

        int Answer = Calculate();

        cout << "#" << test << " " << Answer << "\n";

    }

    return 0;
}