#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

struct info {
	int id;
	int order;
	string s;

	bool operator<(info next) const {
		if (id < next.id) return true;
		else if (id > next.id) return false;
		else {
			if (order < next.order) return true;
			else return false;
		}
	}
};

info arr[100000];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int id;
		string name;
		cin >> id >> name;
		arr[i] = { id,i,name };
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		cout << arr[i].id << " " << arr[i].s << "\n";
	}

	return 0;

}