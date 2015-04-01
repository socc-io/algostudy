__author__ = 'becxer'

STACK = 0
SIZE = 0

class Node :
    def __init__(self,type,value):
        self.type = type
        self.value = value
        self.next_node = None

    def setNextNode(self,next_node):
        self.next_node = next_node

'''Linked list ROOT node'''
ROOT = Node("R",-99)

def add_poop (a,b) :
    global STACK
    global ROOT
    global SIZE

    now = ROOT
    SIZE = 0

    '''tag for stack'''
    start = 0
    end = 0
    '''------------'''

    na = Node('s',a)
    nb = Node('e',b)

    '''Find A node location'''
    while True :
        if now.type == 's':
            if STACK == 0:
                start = now.value
            STACK += 1
        elif now.type == 'e' :
            STACK -= 1
            if STACK == 0:
                SIZE += (now.value - start)

        if now.value <= na.value and ( now.next_node == None or now.next_node.value >= na.value) :
            na.next_node = now.next_node
            now.next_node = na
            now = now.next_node
            break
        else :
            now = now.next_node

    '''Find B node location'''
    while True :
        if now.type == 's':
            if STACK == 0:
                start = now.value
            STACK += 1
        elif now.type == 'e' :
            STACK -= 1
            if STACK == 0:
                SIZE += (now.value - start)
        if now.value <= nb.value and ( now.next_node == None or now.next_node.value >= nb.value) :
            nb.next_node = now.next_node
            now.next_node = nb
            now = now.next_node
            break
        else :
            now = now.next_node

    '''Find OTHER node to be collect poop'''
    while True :
        if now.type == 's':
            if STACK == 0:
                start = now.value
            STACK += 1
        elif now.type == 'e' :
            STACK -= 1
            if STACK == 0:
                SIZE += (now.value - start)
        if  now.next_node == None :
            break
        else :
            now = now.next_node


def ask() :
    global SIZE
    print str(SIZE)

def printer() :
    global ROOT
    here = ROOT
    while True:
        print "-["+str(here.type) + ":" + str(here.value) + "]-"
        if here.next_node == None:
            break
        else:
            here = here.next_node



'''Input code'''
W,Q = map(int, str(raw_input()).split())
for i in range(Q):
    x = map(int, str(raw_input()).split())
    if x[0] == 0 :
        add_poop(x[1],x[2])
    elif x[0] == 1 :
        ask()
    elif x[0] == 2 :
        printer()
