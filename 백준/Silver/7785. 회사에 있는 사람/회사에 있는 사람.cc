#include<iostream>
#include<unordered_set>
#include<algorithm>

using namespace std;

unordered_set<string> us;
string sarr[100001];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		string name, query;
		cin >> name >> query;

		if (query == "enter") us.insert(name);
		else if (query == "leave") us.erase(name);
	}

	int cnt = 0;
	for (auto it = us.begin(); it != us.end(); it++) {
		sarr[cnt] = *it;
		cnt++;
	}

	sort(sarr, sarr + cnt);

	for (int i = cnt-1; i >= 0; i--) {
		cout << sarr[i] << "\n";
	}

	return 0;
}