n = int(raw_input())
ls = map(int,str(raw_input()).split())
ls.sort()
res = ''
for i in range(n):
	if n%2 == 1 and i == n/2:
		res += str(ls[i])
	if i >= n/2 :
		break
	res += str(ls[i]) + ' ' + str(ls[n-1-i])+ ' '

print res
