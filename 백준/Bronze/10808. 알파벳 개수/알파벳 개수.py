my_str = input()
answer = []
for _ in range(26) :
  answer.append(0)

for alphabet in my_str :
  answer[ord(alphabet)-ord('a')] += 1

for i in range(26) :
  print(answer[i], end=" ")