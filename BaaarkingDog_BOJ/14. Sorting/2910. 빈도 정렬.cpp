#include<iostream>
#include<unordered_map>
#include<algorithm>

using namespace std;

struct info {
	int num;
	int cnt;
	int time;

	bool operator<(info next) const {
		if (cnt < next.cnt) return false;
		else if (cnt > next.cnt) return true;
		else {
			if (time < next.time) return true;
			else return false;
		}
	}
};

info arr[1000];
unordered_map<int, pair<int,int>> um;

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N, C;
	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		um[temp].first++;
		if(um[temp].first==1) um[temp].second = i;
	}
	int index = 0;
	for (auto it = um.begin(); it != um.end(); it++) {
		arr[index] = { (*it).first, (*it).second.first, (*it).second.second };
		index++;
	}

	sort(arr, arr + index);

	for (int i = 0; i < index; i++) {
		for (int j = 0; j < arr[i].cnt; j++) {
			cout << arr[i].num << " ";
		}
	}

	return 0;
}