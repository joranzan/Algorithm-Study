#include<iostream>
#include<string>

using namespace std;

string s1, s2;

void Recursion(int depth) {
    if (depth < 0) return;
    int n1 = int(s1[depth]) - '0';
    int n2 = int(s2[depth]) - '0';
    if (n1 == n2) Recursion(depth - 1);
    else if (n1 > n2) {
        for (int i = 2; i >= 0; i--) {
            cout << s1[i];
        }
    }
    else if (n1 < n2) {
        for (int i = 2; i >= 0; i--) {
            cout << s2[i];
        }
    }
}

int main() {

    cin >> s1 >> s2;

    Recursion(2);

    return 0;
}