maxRow = 0
maxCol = 0
maxNum = -1

num = [list(map(int,input().split())) for _ in range(9)]

for i in range(9):
    for j in range(9):
        if num[i][j]>maxNum:
            maxNum = num[i][j]
            maxRow = i
            maxCol = j


print(maxNum)
print(maxRow + 1, maxCol + 1)