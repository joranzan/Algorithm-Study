#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main() {

	string s1;
	string s2;

	cin >> s1;
	cin >> s2;

	int prev = 0;
	int num1 = stoi(s1);
	int sum = 0;
	for (int i = 2; i >= 0; i--) {
		int num2 = int(s2[i] - '0');
		
		cout << num1 * num2 << "\n";

		int add = (num1 * num2) * (pow(10, 2 - i));
		sum += add;

	}
	cout << sum;

	return 0;
}