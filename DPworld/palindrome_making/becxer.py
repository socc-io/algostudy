a = str(raw_input())
b = a[::-1]

dp = [[0 for x in range(len(a))] for x in range(len(a))]
for ib, chb in enumerate(b):
    if ib == 0:
        for ia, cha in enumerate(a):
            if chb == cha:
                dp[0][ia] = 1
    else:
        for ia, cha in enumerate(a):
            if ia > 0 and chb == cha and dp[ib-1][ia-1] >= 1:
                dp[ib][ia] += dp[ib-1][ia-1] + 1

max_len = 0
for idx, row in enumerate(dp):
    if max_len < dp[idx][len(a)-1]:
        max_len = dp[idx][len(a)-1]

print len(a) * 2 - max_len
