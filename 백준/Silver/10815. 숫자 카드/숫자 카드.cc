#include<iostream>
#include<string>
#include<set>

using namespace std;

int DAT[10000001];
int DAT2[10000001];


int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        if (temp >= 0) DAT[temp] = 1;
        else if (temp < 0) DAT2[abs(temp)] = 1;
    }

    int M; 
    cin >> M;
    for (int i = 0; i < M; i++) {
        int temp;
        cin >> temp;
        if (temp >= 0) {
            if (DAT[temp]) cout << "1 ";
            else cout << "0 ";
        }
        else if (temp < 0) {
            if(DAT2[abs(temp)] == 1) cout << "1 ";
            else cout << "0 ";
        }
    }


    return 0;
}