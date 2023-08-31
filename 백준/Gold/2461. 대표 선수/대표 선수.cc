#include <iostream>
#include <algorithm>
using namespace std;

struct Std {
	int num;
	int stat;
};

bool cmp(Std a, Std b) {
	if (a.stat < b.stat) return true;
	if (a.stat > b.stat) return false;
	return false;
}

Std students[1000 * 1000];

int n; // 학급의 수
int m; // 학생의 수

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	int idx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int s;
			cin >> s;
			// 0 ~ n 학급
			students[idx] = { i, s };
			idx++;
		}
	}
	// 능력치순으로 정렬
	sort(students, students + (n * m), cmp);

	int left = 0;
	int right = 0;
	int check[1000] = { 0, }; // 현재 반 구성 인원 체크
	int cnt = 0; // 모든 반 인원들이 포함되었는지 확인 
	int ans = 2134567890;

	// 첫번째 학생 투입 
	check[students[left].num]++;
	cnt++;

	while (right <= idx - 1) {
		// 모든 반 인원들이 구성되었다면
		if (cnt == n) {
			// 최저값 갱신
			if (students[right].stat - students[left].stat < ans)
				ans = students[right].stat - students[left].stat;
			// left의 학생을 제외
			check[students[left].num]--;
			// left 학생을 뺏을 때, 해당 학급의 학생이 모두 빠진다면 cnt 감소
			if (check[students[left].num] == 0)
				cnt--;
			// left 포인터 이동
			left++;
		}
		// 아직 포함되지 않은 반 학생이 있다면
		else {
			// right 포인터 이동
			right++;
			// 만약 처음 들어온 반 학생이라면 cnt 누적
			if (check[students[right].num] == 0)
				cnt++;
			// right 쪽의 학생 포함
			check[students[right].num]++;
		}
	}
	cout << ans;
}