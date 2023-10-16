#include <iostream>
#include<vector>

using namespace std;
//문제 분석
//1. 사내 메신저 준비 (100)
//0~N번 채팅방 (0:Root)
//parents(1~N)
//authority(1~N) -> 상위로 올라갈 수 있는 power
//
//2. 알림망 ON/OFF (200)
//On -> Off
//Off -> On
//Off시 그 부모로 못감

//3. 권한 세기 변경 (300)
//power로 변경
//
//4. 부모 채팅방 교환 (400)
//부모 서로 바꿔줌 (자식도 그대로 가져감) (authority 배열도 변경)

//5. 알림을 받을 수 잇는 채팅방 수 조회 (500)
// c번 채팅방까지 알림이 도달할 수 있는 서로 다른 채팅방 수
//반대로 재귀로 부모->자식으로 타고들어가면서
//authority >= depth면 cnt++

struct chat {
    int id;
    int parent;
    vector<int> child;
    int power;
    bool exe;
};

int N, Q;
chat Info[100001];
int cnt = 0;

void Ready() {
    //1. 사내 메신저 준비 (100)
    //0~N번 채팅방 (0:Root)
    //parents(1~N)
    //authority(1~N) -> 상위로 올라갈 수 있는 power
    vector<int> init;
    for (int i = 0; i <= N; i++) {
        Info[i] = { i,0,init,0,true };
    }
    //Root Node는 부모 없음 ㅋ
    for (int i = 1; i <= N; i++) {
        int p;
        cin >> p;
        Info[i].parent = p;

        Info[p].child.push_back(i);

    }
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        Info[i].power = a;
    }

}
void Toggle() {
    //2. 알림망 ON/OFF (200)
    //On -> Off
    //Off -> On
    //Off시 그 부모로 못감
    int c;
    cin >> c;
    if (Info[c].exe) {
        Info[c].exe = false;
    }
    else {
        //Temp[c] = Parent[c];
        Info[c].exe = true;
    }
}

void changePower() {
    //3. 권한 세기 변경 (300)
    //power로 변경
    int c, power;
    cin >> c >> power;
    Info[c].power = power;
}
void swapParent() {
    int c1, c2;
    cin >> c1 >> c2;

    for (int i = 0; i < Info[Info[c1].parent].child.size(); i++) {
        if (Info[Info[c1].parent].child[i] == c1) Info[Info[c1].parent].child[i] = c2;
    }

    for (int i = 0; i < Info[Info[c2].parent].child.size(); i++) {
        if (Info[Info[c2].parent].child[i] == c2) Info[Info[c2].parent].child[i] = c1;
    }

    swap(Info[c1].parent, Info[c2].parent);
    
}

void DFS(int now, int depth) {
 
    if (Info[now].child.size() == 0) return;

    for (int i = 0; i < Info[now].child.size(); i++) {
        int next = Info[now].child[i];
        if (!Info[next].exe) continue;
        if (Info[next].power >= depth) cnt++;
        
        

        DFS(next, depth + 1);
    }
}

void Verify() {

    cnt = 0;
    int c;
    cin >> c;

    DFS(c, 1);

    cout << cnt << "\n";

}



void input() {
    cin >> N >> Q;
}

void solution() {

    for (int i = 0; i < Q; i++) {
        int cmd;
        cin >> cmd;

        if (cmd == 100) {
            Ready();
        }
        else if (cmd == 200) {
            Toggle();
        }
        else if (cmd == 300) {
            changePower();
            
        }
        else if (cmd == 400) {
            swapParent();
            //int debugging = -1;
        }
        else if (cmd == 500) {
            Verify();
        }
    }

}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    input();
    solution();


    return 0;
}