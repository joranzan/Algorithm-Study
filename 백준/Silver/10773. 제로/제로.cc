#include<iostream>
#include<vector>

using namespace std;

int N;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	vector<int> v;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (num == 0) v.pop_back();
		else v.push_back(num);
	}

	int sum = 0;

	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
	}

	cout << sum;

	return 0;
}