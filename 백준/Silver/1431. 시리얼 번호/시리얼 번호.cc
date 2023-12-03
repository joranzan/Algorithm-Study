#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


struct info {
	string serial;
	int len;
	int sum;

	bool operator<(info next) const {
		if (len < next.len) return true;
		else if (len > next.len) return false;
		else {
			if (sum < next.sum) return true;
			else if (sum > next.sum) return false;
			else {
				if (serial < next.serial) return true;
				else return false;
			}
		}
	}
};


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	info arr[50];
	cin >> N;

	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		int sum = 0;
		int len = 0;
		for (int j = 0; j < s.size(); j++) {
			len++;
			if (s[j] >= 'A') continue;
			sum += int(s[j] - '0');
		}
		arr[i] = { s,len, sum };
	}

	sort(arr, arr + N);

	for (int i = 0; i < N; i++) {
		cout << arr[i].serial << "\n";
	}

	return 0;
}