#include<iostream>

using namespace std;

//K개 미생물 군집
//NxN Map
//가장 자리: 특수한 약품


//최초 군집 정보
// row, col, 미생물 수 , 이동방향(상하좌우 : 방향배열 만들기)
// 
// 규칙
//1시간마다 이동방향 1칸 이동
//약품에 도착 : 미생물 수 /= 2   이동방향 반대
//두개 이상 군집에 모이면 합쳐짐 
//(미생물 총합, 미생물 수 가장 많은 군집의 이동방향) -> 우선순위 큐? 그냥 정렬 후 비교?

//M시간 뒤 미생물 수의 총합



//vector에 미생물 군집 저장
//M만큼 반복문
// 
// vector크기만큼 반복하며
// next_r,next_c 계산
// 만약 약품! -> (방향, 크기) 업데이트 -> 위치는 약품위치 그대로
// 
// um에 넣기!
// 
//반복문 내에 unordered_map 만들기 key: 좌표   value: vector<int, int> 
//um에 key값에 대해 value에 push_back

//다 돌면 다시 미생물 군집 vector에 넣기 (iterator 활용)
//-> value가 여러개면 (미생물 기준)오름차순 정렬, dir 업데이트



int main() {

	


	return 0;
}