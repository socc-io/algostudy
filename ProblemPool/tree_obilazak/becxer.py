from Queue import Queue
import sys
q1 = Queue()
q2 = Queue()
q3 = Queue()
level = int(raw_input())
tree = map(int,str(raw_input()).split())

fstart = 0
fend = len(tree)-1
q1.put(fstart)
q2.put(fend)
q3.put(0)

nlevel = 0
while True:
	if q1.empty():
		break
	nstart = q1.get()
	nend = q2.get()
	plevel = nlevel
	nlevel = q3.get()
	if plevel != nlevel :
		print ""
	sys.stdout.write(str(tree[(nend+nstart)/2])+" ")
	if nend - nstart > 1 :
		q1.put(nstart)
		q2.put((nstart+nend)/2-1)
		q3.put(nlevel+1)
		q1.put((nstart+nend)/2+1)
		q2.put(nend)
		q3.put(nlevel+1)
		

