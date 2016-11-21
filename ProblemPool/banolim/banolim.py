a = int(raw_input())
print a

def ban(N, z):
    if N < z :
        return N
    zn_1 = N % z
    
    if z != 1:    
        zn = zn_1 / (z / 10)
    else :
        zn = zn_1
    if zn >= 5:
        N += z
    else :
        N -= zn_1
    return ban(N, z * 10)

for i in range(9):
    n = int(raw_input())
    print ban(n, 1)
