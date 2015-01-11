
def hanoi(n,f,z,t):
	if n > 0 :
		hanoi(n-1,f,t,z)
		print str(f) + " -> " + str(t)
		hanoi(n-1,z,f,t)

print hanoi(3,1,2,3)
