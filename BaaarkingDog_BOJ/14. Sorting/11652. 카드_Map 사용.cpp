#include<iostream>
#include<algorithm>
#include<unordered_map>

using namespace std;


unordered_map<long long, int> m;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		long long num;
		cin >> num;
		m[num]++;
	}

	int maxCnt = 0;
	long long maxNum = 0;
	for (auto it = m.begin(); it != m.end(); it++) {
		if (maxCnt > (*it).second) continue;

		if (maxCnt < (*it).second) {
			maxNum = (*it).first;
			maxCnt = (*it).second;
		}
		else if (maxCnt == (*it).second) {
			if (maxNum > (*it).first) {
				maxNum = (*it).first;
			}
		}
	}

	cout << maxNum;

	return 0;
}