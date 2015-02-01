n = int(raw_input())
ls = map(int,str(raw_input()).split())
seq_list = [0] * 1000001
max = 0
for i in range(n):
	seq_list[ls[i]] = seq_list[ls[i]-1] + 1
	if max < seq_list[ls[i]] : max = seq_list[ls[i]]
print str(n-max)
