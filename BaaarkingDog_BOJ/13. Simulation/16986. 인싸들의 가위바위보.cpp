#include<iostream>

using namespace std;


//�ϴ��� ���
//1. �ʿ��� �¼�, ��� ���� ���� ���ϱ�

//��� ����
//1. ��� ��� : ���� ���� �� ���� ����� �̱� ������ ����
//2. ���� ����� ���� - ���� ��� ���� ���� ��� -> ���� ����
//3. Ư�� ����� �̸� ���ǵ� �¼��� �޼��� �� ���� (2�� ����) �ݺ�
//4. ���ǵ� �¼��� ���ʷ� �޼��� ��� -> ���!


int N, K;
int Standard[10][10] = { 0, }; 
//2: ���� �� �̱� 
//1: ��� 
//0: ���� ������ ��
int KyungHee[21] = { 0, };
int MinHo[21] = { 0, };

bool flag = false;
int J_Sum = 0;
int K_Sum = 0;
int M_Sum = 0;
int Visited[10] = { 0, };

void DFS(int depth, int foe, int orderJ) {  //1: ���� 2: MinHo  
											//orderJ  1: ��  2: ��
	if (J_Sum >= 3) {
		flag = true;
		return;
	}
	if (depth > N) {
		return;
	}


	for (int i = 1; i <= N; i++) {
		if (Visited[i] == 1) continue;
		int foeChoice;
		if (foe == 1) {
			foeChoice = KyungHee[depth];
		}
		else if (foe == 2) {
			foeChoice = MinHo[depth];
		}

		if (orderJ == 1) {   //���ΰ��� �ռ����϶�
			int result = Standard[i][foeChoice];

			if (result == 2) {  //���ΰ��� �̰��� ��
				
				
			}
			else {  //���ΰ��� ���ų� ���� ��

			}

		}
		else if (orderJ == 2) { //���ΰ��� �޼����϶�
			int result = Standard[i][foeChoice];

			if (result == 0) {  //���ΰ��� ������

			}
			else {   //���ΰ��� �̱�ų� ����� ��

			}

		}

	}


}


void input() {
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Standard[i][j];
		}
	}

	for (int i = 1; i <= 20; i++) {
		cin >> KyungHee[i];
	}

	for (int i = 1; i <= 20; i++) {
		cin >> MinHo[i];
	}
}

void solution() {
	//���� ���� ��ȣ ��




}


int main() {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	input();
	solution();

	return 0;
}

//��ǥ : ��� �յ��� �ٸ��� ���� ����� �� �ִ°�?
// ������ ��ſ� ���л�Ȱ�� ���� �ν� ������������ ��ǥ �־���
// ����, ��ȣ�� �� �յ����� ������ �־����� ��