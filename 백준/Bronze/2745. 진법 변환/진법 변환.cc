#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int main() {

    string N;
    int B;
    cin >> N >> B;

    int sum = 0;

    for (int i = 0; i < N.length(); i++) {
        char c = N[i];
        int temp;
        if (c >= 'A' && c <= 'Z') {
            temp = 10 + int(c - 'A');
        }
        else {
            temp = int(c - '0');
        }
        sum += (temp * pow(B, N.length() - 1 - i));
    }

    cout << sum;

    return 0;
}