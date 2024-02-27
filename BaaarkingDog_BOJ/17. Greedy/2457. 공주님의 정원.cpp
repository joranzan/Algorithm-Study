#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct flower {
	int startMonth;
	int startDay;
	int endMonth;
	int endDay;

	//���ı���
	/*
	���� ��, ���� �� ��������
	*/
	bool operator<(flower next) const {
		if (startMonth < next.startMonth) return true;
		else if (startMonth > next.startMonth) return false;
		else {
			if (startDay < next.startDay) return true;
			else return false;
		}
	}
};

int N;
flower Flower[100001];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> Flower[i].startMonth >> Flower[i].startDay;
		cin >> Flower[i].endMonth >> Flower[i].endDay;
	}
	//���� �Ǵ� ��¥ ���� �������� ����
	sort(Flower, Flower + N);

	int Answer = 0;
	int pivotMonth = 3;   //���� ��
	int pivotDay = 1;     //���� ��
	int pivotIndex = 0;   //������ ���õ� ���� ���� �ε���
	while (pivotMonth < 12) {

		flower maxCandi = { 0,0,0,0 };
		bool valid = false;

		for (int i = pivotIndex; i < N; i++) {
			flower now = Flower[i];
			//if (now.startMonth > pivotMonth) continue;
			//���� �Ǵ� Month�� ���� Month���� ũ�ٸ� ���̻� Ž�� X
			if (now.startMonth > pivotMonth) {
				//���õ� ���� ���ٸ� �Ұ����ϹǷ� return 0
				if (!valid) {
					cout << "0";
					return 0;
				}
				//���õ� ���� �������� ���� Turn �Ѿ
				break;
			}
			//���� ���̶�� �Ǵ� �� �������� ���ذ� ��
			else if (now.startMonth == pivotMonth) {
				if (now.startDay <= pivotDay) {
					//�ռ� ���õ� �ĺ����� ���� ���� ���Ķ�� ����
					if (now.endMonth > maxCandi.endMonth) {
						maxCandi = now;
						valid = true;
						pivotIndex = i + 1;
					}
					else if (now.endMonth == maxCandi.endMonth) {
						if (now.endDay > maxCandi.endDay) {
							maxCandi = now;
							valid = true;
							pivotIndex = i + 1;
						}
					}
				}
				else continue;
			}
			//��/�� ��� ������ �ĺ� ���� ��� �����Ѵٸ�
			else {
				//�ռ� ���õ� �ĺ����� ���� ���� ���Ķ�� ����
				if (now.endMonth > maxCandi.endMonth) {
					maxCandi = now;
					valid = true;
					pivotIndex = i + 1;
				}
				else if (now.endMonth == maxCandi.endMonth) {
					if (now.endDay > maxCandi.endDay) {
						maxCandi = now;
						valid = true;
						pivotIndex = i + 1;
					}
				}
			}
		}

		if (!valid) {
			cout << "0";
			return 0;
		}
		//���� ��¥ ����
		pivotMonth = maxCandi.endMonth;
		pivotDay = maxCandi.endDay;
		Answer++;

	}

	cout << Answer;

	return 0;
}