#include<iostream>
#include<algorithm>

using namespace std;


int arr[100001] = { 0, };

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	
	cin >> N;

	//k���� ���� w �߷��� ��ü ���ø� 

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	

	sort(arr, arr + N);

	int Answer = 0;

	for (int i = 0; i < N; i++) {
		int result = arr[i] * (N - i);
		Answer = max(result, Answer);
	}

	cout << Answer;

	return 0;
}