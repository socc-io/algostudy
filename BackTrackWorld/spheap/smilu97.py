tmp = [int(k) for k in raw_input().split()]
mapx = tmp[0]
mapy = tmp[1]
map = []
cost = [[0]*mapy for asdf in range(mapx)]

def printmap() :
	print '*'*30
	for i in range(mapx) :
		tstr = ''
		for j in range(mapy) :
			tstr += str(map[i][j]) + ' '
		print tstr

def printcost() :
	print '*'*30
	for i in range(mapx) :
		tstr = ''
		for j in range(mapy) :
			tstr += str(cost[i][j]) + ' '
		print tstr


for i in range(mapx) :
	map.append([int(num) for num in raw_input().split()])

tmp = [int(k)-1 for k in raw_input().split()]
startx = tmp[0]
starty = tmp[1]
tmp = [int(k)-1 for k in raw_input().split()]
destx = tmp[0]
desty = tmp[1]

neighbor = [[-1,0], [1,0], [0,1], [0,-1]]

cost[startx][starty] = map[startx][starty]


def dijkstra() :
	min = 99999
	min_x = -1
	min_y = -1
	for i in range(mapx) :
		for j in range(mapy) :
			if cost[i][j] == 0 :
				for k in range(4) :
					x = i+neighbor[k][0]
					y = j+neighbor[k][1]
					if x>=0 and x<mapx and y>=0 and y<mapy :
						if cost[x][y] != 0 :
							newval = cost[x][y] + map[i][j]
							if newval < min  :
								min = newval
								min_x = i
								min_y = j
	cost[min_x][min_y] = min
	if min_x == destx and min_y == desty :
		return True
	else :
		return False

for i in range(mapx*mapy) :
	printcost()
	finded = dijkstra()
	if finded == True :
		break;

printmap()
printcost()
print '*'*30
print 'Cost from %d, %d to %d, %d is : %d' % (startx+1, starty+1, destx+1, desty+1, cost[destx][desty])


