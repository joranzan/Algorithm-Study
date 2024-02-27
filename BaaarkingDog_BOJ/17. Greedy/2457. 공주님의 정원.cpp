#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct flower {
	int startMonth;
	int startDay;
	int endMonth;
	int endDay;

	//정렬기준
	/*
	시작 월, 시작 일 오름차순
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
	//꽃의 피는 날짜 기준 오름차순 정렬
	sort(Flower, Flower + N);

	int Answer = 0;
	int pivotMonth = 3;   //기준 월
	int pivotDay = 1;     //기준 일
	int pivotIndex = 0;   //이전에 선택된 꽃의 다음 인덱스
	while (pivotMonth < 12) {

		flower maxCandi = { 0,0,0,0 };
		bool valid = false;

		for (int i = pivotIndex; i < N; i++) {
			flower now = Flower[i];
			//if (now.startMonth > pivotMonth) continue;
			//만약 피는 Month가 기준 Month보다 크다면 더이상 탐색 X
			if (now.startMonth > pivotMonth) {
				//선택된 꽃이 없다면 불가능하므로 return 0
				if (!valid) {
					cout << "0";
					return 0;
				}
				//선택된 꽃을 기준으로 다음 Turn 넘어감
				break;
			}
			//같은 달이라면 피는 일 기준으로 기준과 비교
			else if (now.startMonth == pivotMonth) {
				if (now.startDay <= pivotDay) {
					//앞서 선택된 후보보다 지는 날이 이후라면 갱신
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
			//월/일 모두 무조건 후보 조건 모두 만족한다면
			else {
				//앞서 선택된 후보보다 지는 날이 이후라면 갱신
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
		//기준 날짜 갱신
		pivotMonth = maxCandi.endMonth;
		pivotDay = maxCandi.endDay;
		Answer++;

	}

	cout << Answer;

	return 0;
}