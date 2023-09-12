#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;


int N, M;
int Input[10] = { 0, };   //�ش� �ε����� �Է� ���� ����
vector<int> Answer; //�� ���ڸ� ���� �迭
bool Visited[10] = { 0, };  //�ش� �ε����� �湮�ߴ��� ����


void DFS(int depth) {
	if (depth >= M) {
		for (int i = 0; i < M; i++) {
			cout << Answer[i] << " ";
		}
		cout << "\n";
		return;
	}
	int lastNum = 0;

	for (int i = 0; i < N; i++) {   //0�� �ε������� N-1�ε�������
		if (Visited[i] == 1) continue; //�ش� �ε��� �湮�ߴٸ� ����
		if (Input[i] == lastNum) continue; //�ε����� �ٸ����� ���� ���� ��� ����
		
		
		//������ ���� ����(���� �ε������� ���� ������ ���� �ֱ� ������ ó���ϱ� ���ؼ�)
		lastNum = Input[i];    
		
		Visited[i] = true;
		Answer.push_back(Input[i]); //���� �迭�� ��� �ֱ�
		
		DFS(depth + 1);

		Visited[i] = false;
		Answer.pop_back();


	}

}


int main() {

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		
		cin >> Input[i];
	}
	sort(Input, Input + N);

	DFS(0);


	return 0;
}

