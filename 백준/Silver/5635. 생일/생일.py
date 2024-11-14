n = int(input())

infos = [list(map(str, input().split())) for _ in range(n)]

max_student = ""
max_year = 2011
max_month = 13
max_day = 40

min_student = ""
min_year = 1980
min_month = 0
min_day = 0

for info in infos:
    if int(info[3]) < max_year:
        max_year = int(info[3])
        max_month = int(info[2])
        max_day = int(info[1])
        max_student = info[0]
    elif int(info[3]) == max_year:
        if int(info[2]) < max_month:
            max_year = int(info[3])
            max_month = int(info[2])
            max_day = int(info[1])
            max_student = info[0]
        elif int(info[2]) == max_month:
            if int(info[1]) < max_day:
                max_year = int(info[3])
                max_month = int(info[2])
                max_day = int(info[1])
                max_student = info[0]

    if int(info[3]) > min_year:
        min_year = int(info[3])
        min_month = int(info[2])
        min_day = int(info[1])
        min_student = info[0]
    elif int(info[3]) == min_year:
        if int(info[2]) > min_month:
            min_year = int(info[3])
            min_month = int(info[2])
            min_day = int(info[1])
            min_student = info[0]
        elif int(info[2]) == min_month:
            if int(info[1]) > min_day:
                min_year = int(info[3])
                min_month = int(info[2])
                min_day = int(info[1])
                min_student = info[0]

print(f"{min_student}\n{max_student}")