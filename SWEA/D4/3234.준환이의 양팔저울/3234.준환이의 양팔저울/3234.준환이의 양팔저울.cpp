#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;


//N개의 양팔저울, 추 (1이상 9이하)
// 추 올리는 방법 N! 가지
//각 양팔 저울: 왼쪽 오른쪽 -> 2^N * N!


//조건) 왼쪽 무게의 총합 >= 오른쪽 무게의 총합


//DFS로 하나씩 더해가며 탐색

int Weight[10]={0};    //무게 입력받음
static int factorial[10] = { 0 };
static int exponential[10] = { 0 };
bool Visited[10] = { false };

int N;
int Sum = 0;
int Answer = 0;

void DFS(int depth, int left, int right) {   //total: 현재 합, num: 현재 합해진 개수
    
    //기저 조건
    if (depth >= N) {
        if (left >= right) {
            Answer++;
        }
        return;
    }

    if (left >= Sum - left) {   //이미 반 넘었으면 더 계산할 필요없음
        Answer = Answer + factorial[N - depth] * exponential[N - depth];
        return;
    }


    //반복문
    //index 부터 숫자의 개수만큼 
    for (int i = 0; i < N; i++) {
        
        if (Visited[i]) continue;

        //왼쪽 추가
        Visited[i] = true;
        DFS(depth + 1, left + Weight[i], right);
        Visited[i] = false;

        if (left < right + Weight[i]) continue;

        //오른쪽 추가
        Visited[i] = true;
        DFS(depth + 1, left, right + Weight[i]);
        Visited[i] = false;
    }

}


int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    factorial[0] = 1;
    exponential[0] = 1;

    for (int i = 1; i <= 9; i++) {
        factorial[i] = factorial[i - 1] * i;
        exponential[i] = exponential[i - 1] * 2;
    }

    int T;
    cin >> T;
    for (int test = 1; test <= T; test++) {

        cin >> N;

        //초기화하기
        Answer = 0;
        Sum = 0;
         


        for (int i = 0; i < N; i++) {
            cin >> Weight[i];
            Sum += Weight[i];
        }

        //sort(Weight.begin(), Weight.end(), greater<int>());

        DFS(0, 0, 0);

        cout << "#" << test << " " << Answer << "\n";

    }

    return 0;
}
