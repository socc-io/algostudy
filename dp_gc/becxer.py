__author__ = 'scv.baek'
n = int(raw_input())
arr = [0 for col in range(100)]
arr[0] = 1
for i in range(2,2*n+1):
    if i %2 == 0:
        for j in range(1,i+1) :
            if j%2 == 0:
                arr[i] += arr[j-2] * arr[i-j]
print arr[2*n]
