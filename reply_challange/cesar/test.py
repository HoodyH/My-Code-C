import math

key = 2
for i in range(1, 200):
    i = (math.log(i, 3) - key)
    print(i)

t1 = [12, 2, 23, 4, 345, 34]
t2 = list(' ' * 6)

pos = 1
i = 1

el = t1[i]
print(el)

el2 = t1[i] ^ i
print(el2)

t2[pos+1] = ((t1[i]) ^ i) ^ (pos+1)

print(t1)
print(t2)
