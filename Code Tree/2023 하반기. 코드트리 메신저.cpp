#include <iostream>
#include<vector>

using namespace std;
//���� �м�
//1. �系 �޽��� �غ� (100)
//0~N�� ä�ù� (0:Root)
//parents(1~N)
//authority(1~N) -> ������ �ö� �� �ִ� power
//
//2. �˸��� ON/OFF (200)
//On -> Off
//Off -> On
//Off�� �� �θ�� ����

//3. ���� ���� ���� (300)
//power�� ����
//
//4. �θ� ä�ù� ��ȯ (400)
//�θ� ���� �ٲ��� (�ڽĵ� �״�� ������) (authority �迭�� ����)

//5. �˸��� ���� �� �մ� ä�ù� �� ��ȸ (500)
// c�� ä�ù���� �˸��� ������ �� �ִ� ���� �ٸ� ä�ù� ��
//�ݴ�� ��ͷ� �θ�->�ڽ����� Ÿ����鼭
//authority >= depth�� cnt++

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
    //1. �系 �޽��� �غ� (100)
    //0~N�� ä�ù� (0:Root)
    //parents(1~N)
    //authority(1~N) -> ������ �ö� �� �ִ� power
    vector<int> init;
    for (int i = 0; i <= N; i++) {
        Info[i] = { i,0,init,0,true };
    }
    //Root Node�� �θ� ���� ��
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
    //2. �˸��� ON/OFF (200)
    //On -> Off
    //Off -> On
    //Off�� �� �θ�� ����
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
    //3. ���� ���� ���� (300)
    //power�� ����
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