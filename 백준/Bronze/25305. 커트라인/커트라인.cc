#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

    int N, X;
    cin >> N >> X;

    vector<int> v(N);

    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end(), greater<int>());

    cout << v[X - 1];

    return 0;
}