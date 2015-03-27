__author__ = 'becxer'
import copy

score_ = [0 for col in range(4)]
board_ = [[0 for col in range(4)] for row in range(4)]

def solve(board,score,T) :
    res = 0
    flag = copy.deepcopy(board)
    nextgame_exist = False
    for i in range(len(board)):
        for j in range(len(board[i])):
            if flag[i][j] == 0  and i != j:
                flag[j][i] = 1
                flag[i][j] = 1
                nextgame_exist = True
                board_win = copy.deepcopy(board)
                score_win = copy.deepcopy(score)
                board_lose = copy.deepcopy(board)
                score_lose = copy.deepcopy(score)
                board_defeat = copy.deepcopy(board)
                score_defeat = copy.deepcopy(score)

                board_win[i][j] = 1
                board_win[j][i] = 1
                score_win[i] += 3
                res += solve(board_win,score_win,T)

                board_lose[i][j] = 1
                board_lose[j][i] = 1
                score_lose[j] += 3
                res += solve(board_lose,score_lose,T)

                board_defeat[i][j] = 1
                board_defeat[j][i] = 1
                score_defeat[i] +=1
                score_defeat[j] +=1
                res += solve(board_defeat,score_defeat,T)

    if not nextgame_exist :
        max = 0
        index_high = 0
        for i in range(len(score)) :
            if score[i] > max :
                max = score[i]
                index_high = i
        if index_high == T :
            return 1
        else :
            return 0
    return res

T = int(raw_input())-1
n = int(raw_input())
for i in range(n):
    fw,bw,fscore,bscore = map(int,str(raw_input()).split())
    fw -= 1
    bw -= 1
    board_[fw][bw] = 1
    board_[bw][fw] = 1
    if fscore == bscore :
        score_[fw] += 1
        score_[bw] += 1
    elif fscore > bscore :
        score_[fw] += 3
    else :
        score_[bw] += 3

print solve(board_,score_,T)/2
