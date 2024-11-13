num = input()
num_list = []
my_list = []

for i in range(10) :
  my_list.append(0)
  num_list.append(0)

for n in num :
  needNum = int(n)
  num_list[needNum] += 1


# print(num_list)



for i in range(9) :
  if num_list[i] != 0 :
    if i != 6 :
      my_list[i] += num_list[i]
  else : continue

six_nine = num_list[6] + num_list[9]

if six_nine % 2 == 0 : 
  six_nine /= 2
else :
  six_nine = six_nine / 2 + 1

maxValue = max(my_list)

if maxValue < six_nine : 
  print(int(six_nine))
else :
  print(int(maxValue))