#include<iostream>
#include<algorithm>

using namespace std;

int A[51] = { 0, };
int B[51] = { 0, };

int main() {

	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> B[i];
	}

	sort(A, A + N);
	sort(B, B + N, greater<int>());

	int Answer = 0;

	for (int i = 0; i < N; i++) {
		Answer += (A[i] * B[i]);
	}

	cout << Answer;

	return 0;
}