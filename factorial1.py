def factorial(n) :
	ret = 1
	for i in range(1,n+1) :
		ret *= i
	return ret

def func(n) :
	val = n
	while val%10 == 0 :
		val /= 10
	return val%10

val = input()
print func(factorial(val))
