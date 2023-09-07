#include<iostream>
#include<cmath>

using namespace std;

//n번 원판을 기둥 3으로 옮기려면 1~n-1번 원판은 기둥 2로 옮겨야함
//n번 원판을 기둥 3으로 옮긴 뒤  1~n-1번 원판을 기둥 3으로 옮김
//
//귀납적 사고 : n-1개일 때 옮길수 있으면 n개일때도 옮길 수 있다


//함수의 정의 (함수는 어떤 역할, 어떤 인자를 받는가?)

// 시작 기둥, 도착 기둥을 인자로 받아야함
//func (int a, int b, int n) -> 원판 n개를 a번 기둥에서 b번 기둥으로 옮기는 방법

//재귀 식 (기둥합: 6)

int ans = 0;

void Recursion(int a, int b, int n) {

	//Basic Condition(원판이 하나일 때 그냥 옮길 수 있음
	if (n == 1) {
		cout << a << " " << b << "\n";
		ans++;
		return;
	}
	//(n-1)개의 원판을 기둥 a에서 b로 옮김 func(a, 6-a-b, n-1)     //기둥 a에서 b가 아닌 다른곳에 옮겨두기
	Recursion(a, 6 - a - b, n - 1);
	ans++;
	//n번 원판을 b로 옮김
	cout << a << " " << b << "\n";
	//나머지 6-a-b 에다가 옮겨놓은 원판들을 b로 옮김 
	Recursion(6 - a - b, b, n - 1);
}



int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int N;
	cin >> N;

	ans = pow(2, N)-1;
	cout << ans << " ";

	Recursion(1, 3, N);

	return 0;
}


//마지막 n번을 옮길 경우 n-1까지 애들을 다 그 다른 곳에 옮겨놔야함
//n-1번을 옮길 때는 n-2까지 애들을 다 그 다른 곳에 옮겨놔야함