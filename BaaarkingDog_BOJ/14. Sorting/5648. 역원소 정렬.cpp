#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

unsigned long arr[100000];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;
	
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;

		string temp;
		for (int i = s.size() - 1; i >= 0; i--) {
			temp.push_back(s[i]);
		}

		arr[i] = stoul(temp);
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		cout << arr[i] << "\n";
	}


	return 0;
}