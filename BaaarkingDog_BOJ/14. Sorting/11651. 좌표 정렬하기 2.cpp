#include<iostream>
#include<algorithm>

using namespace std;

struct pos {
	int y;
	int x;

	bool operator<(pos next) const {
		if (y < next.y) return true;
		else if (y > next.y) return false;
		else {
			if (x < next.x) return true;
			else return false;
		}
	}
};

pos arr[100000];

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		arr[i] = { y, x };
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		cout << arr[i].x << " " << arr[i].y << "\n";
	}

	return 0;
}