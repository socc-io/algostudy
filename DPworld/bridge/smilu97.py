import sys

if __name__ == '__main__' :
	goal = raw_input()
	bridge = (raw_input(), raw_input())
	alphaPos = {}
	alphaPos['R'] = list()
	alphaPos['I'] = list()
	alphaPos['N'] = list()
	alphaPos['G'] = list()
	alphaPos['S'] = list()
	linkList = [[{} for i in range(len(bridge[0]))],[{} for i in range(len(bridge[0]))]]
	for ch in goal :
		if not (ch=='R' or ch=='I' or ch=='N' or ch=='G' or ch=='S') :
			print 1245229260
			sys.exit(0)
	for i in range(2) :
		for j in range(len(bridge[0])) :
			if bridge[i][j] == 'R' :
				alphaPos['R'].append((i,j))
			if bridge[i][j] == 'I' :
				alphaPos['I'].append((i,j))
			if bridge[i][j] == 'N' :
				alphaPos['N'].append((i,j))
			if bridge[i][j] == 'G' :
				alphaPos['G'].append((i,j))
			if bridge[i][j] == 'S' :
				alphaPos['S'].append((i,j))
	for pos in alphaPos[goal[-1]] :
		linkList[pos[0]][pos[1]][''] = 1
	for chIndex in range(len(goal)-2, -1, -1) :
		for finderPos in alphaPos[goal[chIndex]] :
			for searchPos in alphaPos[goal[chIndex+1]] :
				if searchPos[0] == 1 - finderPos[0] and searchPos[1] > finderPos[1] :
					tmp = linkList[searchPos[0]][searchPos[1]].get(goal[chIndex+2:],False)
					if tmp != False :
						tmp2 = linkList[finderPos[0]][finderPos[1]].get(goal[chIndex+1:],False)
						if tmp2 == False:
							linkList[finderPos[0]][finderPos[1]][goal[chIndex+1:]] = tmp
						else :
							linkList[finderPos[0]][finderPos[1]][goal[chIndex+1:]] += tmp
		#print str(chIndex),
		#print linkList
	ansSum = 0
	for pos in alphaPos[goal[0]] :
		tmp = linkList[pos[0]][pos[1]].get(goal[1:],0)
		if tmp != 0 :
			ansSum += tmp
	print ansSum