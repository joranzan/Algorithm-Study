#include<iostream>

using namespace std;

int main() {

    int N;
    cin >> N;
    int maxLine = N * 2 - 1;
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < maxLine; j++) {
            if (j >= i && j < maxLine - i) cout << "*";
            else cout << " ";
        }
        cout << "\n";
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < maxLine; j++) {
            if (j >= i && j < maxLine - i) cout << "*";
            else cout << " ";
        }
        cout << "\n";
    }


    return 0;
}