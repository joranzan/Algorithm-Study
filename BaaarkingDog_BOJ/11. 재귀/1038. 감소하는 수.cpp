#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int N;
int cnt = -1;
bool found = false;

void DFS(vector<int> num,int last_num, int depth, int length) {
		 
	if (depth == length) { //���� length���̸�ŭ ���� ��������� �����ϴ� ���� �ϼ��̹Ƿ� ����++
		cnt++;
		if (cnt == N) { //���� N�� ������ ����
			for (int i = 1; i <= length;i++) {
				cout << num[i];
			}
		}
		return;
	}


	for (int i = 0; i < last_num; i++) {  //���� ���ں��� ����������
		
		num.push_back(i);  //�ϳ� ����
		DFS(num, i, depth + 1, length);  //�״��� ���� ������ ����
		if (found) break;
		num.pop_back();  // (i) �־��� �� �����ϴ� ���� �� ã�� ���ƿ����� i �ٽ� ��

	}
	
}


int main(){

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	//N�� 0�̸� ����� �ʿ����
	if (N == 0) {
		cout << "0";
		return 0;
	}



	//���̰� 1�ڸ��� ���ں��� 10�ڸ��� ���ڱ��� ã��
	for (int i = 1; i <=10; i++) { 
		if (found) break;   //���� ���� ã������ for�� ����
		vector<int> temp;
		temp.push_back(10);  //���ڸ��϶� 0~9���� �;��ϹǷ� �Ǿտ� ����Ʈ�� 10 �־���
							 //�׷��� ���ڸ����� ���� �ֵ� ���� �� 0~9���� �� ���� �� �����ϱ� 
		
		DFS(temp, 10, 0, i); // i�ڸ� ���� �� �����ϴ� ������ �� ã���� ����
	}
	if (cnt < N) cout << "-1";


	return 0;
}