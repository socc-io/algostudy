n = int(raw_input())
list = map(int, str(raw_input()).split())
count  = 0
def swap(i,j):
	global count
	count+=1
	temp = list[i]
	list[i] = list[j]
	list[j] = temp

for i in range(n) :
	if list[i] != i+1 :
		for j in range(i+1,n):
			if list[j] == i+1 :
				swap(i,j)
				break

print count

