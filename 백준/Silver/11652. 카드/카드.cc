#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct info {
	long long num;
	int cnt;

	bool operator<(info next) const {
		if (cnt < next.cnt) return false;
		else if (cnt > next.cnt) return true;
		else {
			if (num < next.num) return true;
			else return false;
		}
	}
};

unordered_map<long long, int> m;
info arr[100000];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		long long num;
		cin >> num;
		m[num]++;
	}

	int cnt = 0;
	for (auto it = m.begin(); it != m.end(); it++) {
		arr[cnt] = { (*it).first, (*it).second };
		cnt++;
	}

	sort(arr, arr + cnt);

	cout << arr[0].num;

	return 0;
}