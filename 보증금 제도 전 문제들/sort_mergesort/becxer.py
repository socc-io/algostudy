def merge(P,Q):
	ip = 0
	iq = 0
	res = []
	while True:
		if ip >= len(P) or iq >= len(Q):
			break 
		if P[ip] > Q[iq]:
			res.append(Q[iq])
			iq += 1
		elif P[ip] <= Q[iq]:
			res.append(P[ip])
			ip += 1
	if ip < len(P):
		res.extend(P[ip:])
	if iq < len(Q):
		res.extend(Q[iq:])
	print str(P) + "+"+str(Q) + "=" +str(res)
	return res

def merge_sort(A):
	if len(A) == 1:
		return A
	elif len(A) == 0:
		return []
	A_p = merge_sort(A[:len(A)/2])
	A_q = merge_sort(A[len(A)/2:])
	return merge(A_p,A_q)

arr = map(int,str(raw_input()).split(" "))
print str(merge_sort(arr))
