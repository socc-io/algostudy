class suffixNode :
	def __init__(self, val) :
		self.parent = None
		self.child = []
		self.val = val

def makeSuffixNode(s) :
	Root = suffixNode(None)
	LongestNode = Root
	for c in s :

