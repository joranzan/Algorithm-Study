#include<iostream>

using namespace std;

//�����м�
//�ڿ��� A�� B�� ���� ���� C�� ���� ������

//�������� ���ϰ� �ٽ� ������ ���
using ll = long long;

ll B, C;
ll Answer = 0;

//(a�� k���� B�� ���� ������)^2 == a�� 2k���� B�� ���� ������

ll DFS(ll a,ll b, ll c) {


	if (b == 1) {   //a�� �ѹ� ���� ���� ������
		return a % c;
	}
	
	//�ϴ� b�� 2�� ������ŭ ���� ���� ������
	ll value = DFS(a, b / 2, c);  //a�� k���� ������
	//������ Value�� a�ѹ� �� ���ϰ� ������ 
	value = value * value % c;   //(a�� k���� B�� ���� ������)^2 == a�� 2k���� B�� ���� ������
	if (b % 2 == 0) return value;
	else return (value * a) % c;
}

int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll A;
	cin >> A >> B >> C;
	cout << DFS(A, B, C);
}

