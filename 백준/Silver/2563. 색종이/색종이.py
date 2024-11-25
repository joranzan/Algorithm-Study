# 가로 세로

N = int(input())
Area = []

for i in range(100):
    line = []
    for j in range(100):
        line.append(0)
    Area.append(line)

# print(Area)

for i in range(N):
    start_x, start_y = map(int, input().split())
    for r in range(start_x, start_x + 10, 1):
        for c in range(start_y, start_y + 10, 1):
            Area[r][c] = 1

Answer = 0

for i in range(100):
    for j in range(100):
        if Area[i][j] == 1:
            Answer += 1


print(Answer)