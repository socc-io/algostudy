def getBiggest(arr) :
	big = -1
	for i in arr :
		if big < i :
			big = i
	return big

def getChainLen(num) :
	val = num
	length = 1
	while val != 1:
		if val%2 == 0 :
			val /= 2
		else :
			val *= 3
			val += 1
		length += 1
	return length
 
input = [int(k) for k in raw_input('Input range : ').split()]
lens = [getChainLen(k) for k in range(input[0], input[1]+1)]
print 'Result : %d' % getBiggest(lens)
