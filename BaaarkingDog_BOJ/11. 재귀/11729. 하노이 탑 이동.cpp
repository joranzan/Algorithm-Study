#include<iostream>
#include<cmath>

using namespace std;

//n�� ������ ��� 3���� �ű���� 1~n-1�� ������ ��� 2�� �Űܾ���
//n�� ������ ��� 3���� �ű� ��  1~n-1�� ������ ��� 3���� �ű�
//
//�ͳ��� ��� : n-1���� �� �ű�� ������ n���϶��� �ű� �� �ִ�


//�Լ��� ���� (�Լ��� � ����, � ���ڸ� �޴°�?)

// ���� ���, ���� ����� ���ڷ� �޾ƾ���
//func (int a, int b, int n) -> ���� n���� a�� ��տ��� b�� ������� �ű�� ���

//��� �� (�����: 6)

int ans = 0;

void Recursion(int a, int b, int n) {

	//Basic Condition(������ �ϳ��� �� �׳� �ű� �� ����
	if (n == 1) {
		cout << a << " " << b << "\n";
		ans++;
		return;
	}
	//(n-1)���� ������ ��� a���� b�� �ű� func(a, 6-a-b, n-1)     //��� a���� b�� �ƴ� �ٸ����� �Űܵα�
	Recursion(a, 6 - a - b, n - 1);
	ans++;
	//n�� ������ b�� �ű�
	cout << a << " " << b << "\n";
	//������ 6-a-b ���ٰ� �Űܳ��� ���ǵ��� b�� �ű� 
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


//������ n���� �ű� ��� n-1���� �ֵ��� �� �� �ٸ� ���� �Űܳ�����
//n-1���� �ű� ���� n-2���� �ֵ��� �� �� �ٸ� ���� �Űܳ�����