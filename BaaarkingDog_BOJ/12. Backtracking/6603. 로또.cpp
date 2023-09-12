#include<iostream>
#include<vector>

using namespace std;

//���� �м�
//�� 6�� ��
// 49���� �� �� ���� K���� �� ���� �� �� �ȿ��� 6�� �����ϴ� ����

//Combination

int K;
int Input[13] = { 0, };
vector<int> Ans;


void Combination(int index , int depth) {

	if (depth >= 6) {
		for (int i = 0; i < Ans.size(); i++) {
			cout << Ans[i] << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = index; i < K; i++) {
		Ans.push_back(Input[i]);
		Combination(i + 1, depth + 1);
		Ans.pop_back();

	}



}


void init() {
	
	Ans.clear();
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> Input[i];
	}
}


int main() {


	while (1) {
		init();
		if (K == 0) return 0;

		Combination(0, 0);
		cout << "\n";

	}



	return 0;
}

//�Է�  
// K .... K���� ��