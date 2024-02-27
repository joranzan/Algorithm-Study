#include<iostream>
#include<deque>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;
    deque<int> dq;
    for (int i = 0; i < N; i++) {
        string query;
        cin >> query;

        if (query == "push") {
            int temp;
            cin >> temp;
            dq.push_back(temp);
        }
        else if (query == "pop") {
            if (dq.size() != 0) {
                cout << dq[0] << "\n";
                dq.pop_front();
            }
            else cout << "-1\n";
        }
        else if (query == "size") {
            cout << dq.size() << "\n";
        }
        else if (query == "empty") {
            if (dq.size() == 0) cout << "1\n";
            else cout << "0\n";
        }
        else if (query == "front") {
            if (dq.size() != 0) cout << dq[0] << "\n";
            else cout << "-1\n";
        }
        else if (query == "back") {
            if (dq.size() != 0) cout << dq[dq.size() - 1] << "\n";
            else cout << "-1\n";
        }
    }

    return 0;
}