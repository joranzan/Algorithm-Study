#include<iostream>
#include<set>
#include<string>

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;
    set<string> s;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        s.insert(str);
    }

    set<pair<int, string>> s2;

    for (auto it = s.begin(); it != s.end(); it++) {
        s2.insert({ (*it).length(), *it});
    }



    for (auto it = s2.begin(); it != s2.end(); it++) {
        cout << (*it).second << "\n";
    }

    return 0;
}