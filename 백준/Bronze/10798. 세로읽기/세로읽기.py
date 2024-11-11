S = [list(input().split()) for i in range(5)]

MaxLen = 0

for i in range(5):
    MaxLen = max(MaxLen, len(S[i][0]))

# print(MaxLen)

for i in range(MaxLen):
    for j in range(5):
        if len(S[j][0]) > i:
            print(S[j][0][i], end="")