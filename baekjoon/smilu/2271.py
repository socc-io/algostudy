
def do_task():
	N = int(input())
	A = [int(k) for k in input().split()]
	m = [0 for _ in A]
	M = [0 for _ in A]
	for p in range(0, N-3):
		m[p+1] = p+1
		M[p+1] = p+1
		for i in range(p+2, N):
			if m[i] > p: break
			m[i] = i if A[m[i-1]] > A[i] else m[i-1]
		for i in range(p+2, N):
			if M[i] > p: break
			M[i] = i if A[M[i-1]] < A[i] else M[i-1]
		for s in range(p+3, N):
			if (A[p]-A[s])*(M[s-1]-m[s-1]) > 0 and\
				A[M[s-1]] > A[p] and A[M[s-1]] > A[s] and\
				A[m[s-1]] < A[p] and A[m[s-1]] < A[s]:
				print('Yes')
				return
	print('No')
	return

for _ in range(int(input())): do_task()
	