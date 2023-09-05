#include<iostream>

using namespace std;

//문제분석
//자연수 A를 B번 곱한 수를 C로 나눈 나머지

//나머지만 곱하고 다시 나누는 방식
using ll = long long;

ll B, C;
ll Answer = 0;

//(a의 k승을 B로 나눈 나머지)^2 == a의 2k승을 B로 나눈 나머지

ll DFS(ll a,ll b, ll c) {


	if (b == 1) {   //a를 한번 곱한 값의 나머지
		return a % c;
	}
	
	//일단 b를 2로 나눈만큼 곱한 값의 나머지
	ll value = DFS(a, b / 2, c);  //a의 k승의 나머지
	//가져온 Value에 a한번 더 곱하고 나머지 
	value = value * value % c;   //(a의 k승을 B로 나눈 나머지)^2 == a의 2k승을 B로 나눈 나머지
	if (b % 2 == 0) return value;
	else return (value * a) % c;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll A;
	cin >> A >> B >> C;
	cout << DFS(A, B, C);
}


