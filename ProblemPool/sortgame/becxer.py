n = int(raw_input())
arr = map(int, str(raw_input()).split())
k = int(raw_input())

max_val = 0
next_max = 0
max_idx = 0
for i in range(k):
    kab = map(int, str(raw_input()).split())
    a = kab[0]
    b = kab[1]
    

res = ''
for i in range(n):
    res += str(arr[i]) + ' '
print res
