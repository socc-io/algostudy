

wordList = 'banana apple automatics robot computer strawberry carrot atom city steam kakaotalk menu expand solution calculus search evaluation star depth talk game'.split()

def problemDescription() :
	print '*'*20 + '\nChange the word\nAuthor : Kim YoungJin\nID: 2016025241\n' + '*'*20

def replace(rawString, fromChar, toChar) : # replace every fromChar in rawString to toChar
	while True :
		findedIndex = rawString.find(fromChar)
		if findedIndex == -1 :
			break
		else :
			rawString = rawString[0:findedIndex] + toChar + rawString[findedIndex + len(fromChar) : ]
	return rawString

if __name__ == '__main__' :
	for word in wordList : # print Every words in wordList
		print word,
	print
	fromChar = '' # get character to be deleted (len : 1, 'a' <= x <= 'z')
	while True :
		fromChar = raw_input('Input the character to delete (a-z) : ')
		if len(fromChar) == 1 :
			if ord('a') <= ord(fromChar[0]) and ord(fromChar[0]) <= ord('z') :
				break
	toChar = '' # get character to be replaced (len : 1, 'a' <= x <= 'z')
	while True :
		toChar =  raw_input('Input the character to replace (a-z) : ')
		if len(toChar) == 1 :
			if ord('a') <= ord(toChar[0]) and ord(toChar[0]) <= ord('z') :
				break
	replacedWordCount = 0
	for word in wordList : # Check every words
		if fromChar in word :
			replacedWordCount += 1
			print '%d. %s --> %s' % (replacedWordCount, word, replace(word, fromChar, toChar))
	print
	print '%d words are changed' % replacedWordCount


