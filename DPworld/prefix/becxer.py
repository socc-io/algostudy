import sys

st_word = []
while True:
    inp = str(raw_input())
    if inp == ".":
        break
    st_word.extend(inp.split())

s = ""
while True:
    input_ = sys.stdin.readline().strip()
    if input_ == '':
        break
    else:
        s += input_

dp = [False for i in range(len(s))]
max_index = -1
for i in range(len(s)):
    for word in st_word:
        if (i+1) - len(word) > 0:
            if dp[i - len(word)] and s[i-len(word)+1:i+1] == word:
                if(max_index < i):
                    max_index = i
                dp[i] = True
        if (i- len(word) +1) == 0:
            if s[i-len(word)+1:i+1] == word:
                if(max_index < i):
                    max_index = i
                dp[i] = True
print s
print dp[:10]                
print max_index + 1
