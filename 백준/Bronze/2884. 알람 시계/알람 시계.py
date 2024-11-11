# 45분 일찍 알람 설정하기

hour, min = input().split()

hour = int(hour)
min = int(min)

min -= 45

if min < 0 :
    min += 60
    hour -= 1

if hour < 0 :
    hour += 24


print(hour,min)


