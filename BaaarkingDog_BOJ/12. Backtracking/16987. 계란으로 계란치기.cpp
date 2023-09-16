#include<iostream>
#include<vector>
#include<cmath>


using namespace std;

// �� ���: ������ , ����
// ������ 0 ���� -> ���� (��� ��� ���Ը�ŭ ����)
// 
// ���� ��ǥ : �ִ��� ���� ����� ����
//1. �Ϸķ� ���� ��� ���ʺ��� ����
//2. ������ ���� ��� �ϳ� �����ؼ� ħ
//3. �տ� �� ��� �����ų�, ������ ���� �ٸ� ��� ������ continue;
//4. ��� ��������
//5. ����ĭ ��� ��� ���� �ݺ�


//�Է�
//N: ����� �� 1�̻� 8����
//������ ����



struct egg {
	int hard;
	int weight;
};

int N;
egg eggs[10] = {};
bool isBroken[10] = { false }; //����� �������� ����
int Answer = 0;


void BackTracking(int depth, int cnt) {

	if (depth >= N || cnt== N) {   //���� ������ ����� ������ ��� OR cnt�� �̹� ��� �� �� ����
		Answer = max(Answer, cnt);
		return;
	}
	

	if (isBroken[depth]) BackTracking(depth + 1, cnt);  //������ ��� �̹� �������¸� �ѱ�
	else {
		if (cnt == N - 1) {   //�ڱ� ���� �� ���� �����̸� �׳� return ������ �� ����
			Answer = max(Answer, cnt); 
			return;
		}

		for (int i = 0; i < N; i++) {
			if (depth == i) continue;  //�ڱ� �ڽ� ���� ��� ����
			if (isBroken[i]) continue; //�̹� ���� ��� ���������� ����

			int nowCnt = cnt;

			//��� ���߸��� ���� ����
			int hard1 = eggs[depth].hard;
			int weight1 = eggs[depth].weight;
			int hard2 = eggs[i].hard;
			int weight2 = eggs[i].weight;

			int after_hard1 = hard1 - weight2;
			int after_hard2 = hard2 - weight1;

			if (after_hard1 <= 0) {
				nowCnt++;
				isBroken[depth] = true;
			}
			if (after_hard2 <= 0) {
				nowCnt++;
				isBroken[i] = true;
			}

			eggs[depth].hard = after_hard1;
			eggs[i].hard = after_hard2;

			BackTracking(depth + 1, nowCnt);

			eggs[depth].hard = hard1;
			eggs[i].hard = hard2;
			isBroken[depth] = false;
			isBroken[i] = false;
		}
	}

}


int main() {

	cin >> N;
	for (int i = 0; i < N; i++) {
		int hard, weight;
		cin >> hard >> weight;
		eggs[i] = { hard,weight };
	}

	BackTracking(0, 0);
	cout << Answer;

	return 0;
}

// ��� 0 ���1 ��� 2
//��� 0 ����
// 1 ġ��, 2ġ�� �� ����
// 1ģ���: 