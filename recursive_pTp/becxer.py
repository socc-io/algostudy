def pTp(n):
	if n == 1 :
		return 1
	return ''+str(pTp(n-1))+str(n)+str(pTp(n-1))
print pTp(4)
