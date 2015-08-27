#!/usr/bin/python
arr = [[0 for i in range(10)] for i in xrange(1001)]
arr[0] = [1 for i in xrange(10)]
for j in xrange(1,1001):
	for p in xrange(10):
		if (p-1)/ 3 == p/3 and p-1 > -1:
			arr[j][p] += arr[j-1][p-1]
		if (p+1)/ 3 == p/3 and p+1 < 10:
			arr[j][p] += arr[j-1][p+1]
		if p + 3 < 10:
			arr[j][p] += arr[j-1][p+3]
		if p - 3 > -1:
			arr[j][p] += arr[j-1][p-3]
	arr[j] = map(lambda x: x % 1234567, arr[j])
testcase = int(raw_input())
for i in xrange(0,testcase):
	n = int(raw_input())
	print sum(arr[n-1]) % 1234567
