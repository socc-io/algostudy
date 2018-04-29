V, E = map(int, input().split())

class Node:
    def __init__(self, f, t, v):
        self.f = f
        self.t = t
        self.v = v

v_visit = [0 for i in range(V)]
n_list = []
for i in range(E):
    f,t,v = map(int,input().split())
    n_list.append(Node(f-1,t-1,v))

import operator
sorted_list = sorted(n_list, key=operator.attrgetter('v'))

value = 0
vcount = 0

for n in sorted_list:
    if v_visit[n.f] and v_visit[n.t]:
        continue
    if(v_visit[n.f] == 0):
        v_visit[n.f] = 1
        vcount += 1
    if(v_visit[n.t] == 0):
        v_visit[n.t] = 1
        vcount += 1
    value += n.v
    if vcount >= V:
        break
    
print([n.v for n in sorted_list])
print(value)
