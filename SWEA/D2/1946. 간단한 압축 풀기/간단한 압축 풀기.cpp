test = int(input())

for t in range(test):
    print(f"#{t+1}")
    index = 0
    num = int(input())
    for i in range(num):
        letter, cnt = input().split()
        cnt = int(cnt)

        for j in range(cnt):
            print(letter, end="")
            index += 1
            if index==10:
                index = 0
                print()
    print()