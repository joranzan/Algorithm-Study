# 홀수 번째 줄 분수
# 그 숫자 ~ 그 숫자 분의 1

# 짝수 번째 줄 분수
# 그 숫자 분의 1 ~ 그 숫자


N = int(input())
Sum = 1
lineNum = 1

while Sum < N :
    lineNum += 1
    Sum += lineNum



# print(lineNum)
# print(Sum)
# 1  1
# 2  3
# 3  6
# 4  10
# 5  15
# 6  21
# 7  28
# 8  36
# 9  45
# 10 55
#
# 홀수 줄인 경우
if lineNum % 2 != 0 :
    bottom = lineNum - (Sum - N)
    top = lineNum + 1 - bottom
    print(top, end='')
    print('/', end='')
    print(bottom, end='')

# 짝수 줄인 경우
else :
    top = lineNum - (Sum - N)
    bottom = lineNum + 1 - top
    print(top, end='')
    print('/', end='')
    print(bottom, end='')