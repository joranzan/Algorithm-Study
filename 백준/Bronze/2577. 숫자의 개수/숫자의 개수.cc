#include<iostream>
#include<string>


using namespace std;

typedef long long ll;

int main() {

	ll A, B, C;
	cin >> A >> B >> C;

	int arr[10] = { 0 };
	ll num = A * B * C;

	string s = to_string(num);

	for (int i = 0; i < s.length(); i++) {

		arr[int(s[i] - '0')]++;

	}

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << "\n";
	}

	return 0;
}