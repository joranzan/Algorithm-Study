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

	sort(Flower, Flower + N);

	int Answer = 0;
	int pivotMonth = 3;
	int pivotDay = 1;
	int pivotIndex = 0;
	while (pivotMonth < 12) {

		flower maxCandi = { 0,0,0,0 };
		bool valid = false;

		for (int i = pivotIndex; i < N; i++) {
			flower now = Flower[i];
			if (now.startMonth > pivotMonth) continue;
			else if (now.startMonth == pivotMonth) {
				if (now.startDay <= pivotDay) {
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
			else {
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

		pivotMonth = maxCandi.endMonth;
		pivotDay = maxCandi.endDay;
		Answer++;

	}

	cout << Answer;

	return 0;
}

/*

N개의 꽃

4,6,9,11 :30일
1,3,5,7,8,10,12 : 31일
2 : 28일


3월 1일 ~ 11월 30일까지 (3월 1일에 피는 꽃, 12월 1일에 지는 꽃)


*/

/*

TC

1월 1일 ~ 5월 31일
1월 1일 ~ 6월 30일
5월 15일 ~ 8월 31일
6월 10일 ~ 12월 10일

cnt=0

기준 날짜 : 3월 1일
1) 지는 날이 기준 날짜 이후 && 시작날 기준날짜 이하인 경우 -> 제일 긴 애들
이런애들 없으면 그냥 0

cnt++
기준 날짜 갱신 : 6월 30일

2) 지는 날이 기준 날짜 이후 && 시작날 기준날짜 이하인 경우 -> 제일 긴 애들
이런 애들 없으면 그냥 0


cnt++
3) 기준 날짜 갱신 : 12월 10일 

---> 11월 30일 이후이므로 탈출


cnt = 2
*/