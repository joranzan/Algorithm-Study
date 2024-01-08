#include<iostream>
#include<vector>



using namespace std;

long long A, B, C;

long long Recursion(int b) {

	if (b == 0) return 1;
	
	long long ret;

	if (b % 2 == 0) {
		ret = Recursion(b / 2);
		return ret * ret % C;
	}
	else {
		ret = Recursion(b - 1);
		return ret * ret % C * A % C;
	}
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	
	cin >> A >> B >> C;

	cout << Recursion(B);


	return 0;
}