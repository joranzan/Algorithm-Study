# (x,y) xkg ycm
# 몸무게도 크고 키도 크면 덩치가 크다
# 덩치 등수는 자신보다 '큰 덩치'의 사람 수
# 큰 덩치 k명이면 자신은 k+ 1등

N = int(input())

Info = [list(map(int, input().split())) for _ in range(N)]

# print(Info)

for i in range(N) :
    cnt = 0
    for j in range(N) :
        if i==j : continue
        else :
            if Info[i][0] < Info[j][0] and Info[i][1] < Info[j][1] :
                cnt += 1

    print(cnt + 1, end=' ')


