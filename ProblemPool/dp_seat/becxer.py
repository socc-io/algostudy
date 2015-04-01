__author__ = 'becxer'

N = int(input())
seat = [0 for tag in range(100)]
seat[0] = 1
seat[1] = 1
for i in range(2,N+1):
    seat[i] = seat[i-1] + seat[i-2]

count = int(input())
sum = 1
start = 0
end = 0
for i in range(count):
    end = int(input())
    sum *= seat[end-start-1]
    start = end
end = N
sum *= seat[end-start]

print(sum)
