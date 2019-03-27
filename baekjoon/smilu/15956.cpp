/*
 * author: smilu97
 */
#include <cstdio>
#include <cstring>

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

char S[1000002];
int S_len;
char R[1000002];
int R_len;

struct Word {
    char* value;
    int len;
    int cnt_integer;
    Word* parent;
    Word(char* value, int len): value(value), len(len) {
        this->parent = this;
        this->cnt_integer = 0;
    }
};

vector<Word*> words;
map<string, Word*> word_map;
vector< pair<Word*, Word*> > eq_relations;
vector< pair<Word*, Word*> > neq_relations;

Word* get_word(char* value)
{
    string s(value);
    
    if (word_map.find(s) != word_map.end()) {
        return word_map[s];
    }

    int len = strlen(value);
    Word* new_word = new Word(value, len);
    words.push_back(new_word);
    word_map[s] = new_word;

    if (isdigit(value[0]) || value[0] == '-') {
        new_word->cnt_integer = 1;
    }

    // printf("word: %s\n", new_word->value);

    return new_word;
}

Word* get_parent(Word* word)
{
    if (word->parent == word) return word;
    return word->parent = get_parent(word->parent);
}

void apply_relation(char* str, int len)
{
    int op_type, op_idx;
    for (op_idx = 0; op_idx < len; ++op_idx) {
        if (str[op_idx] == '=' || str[op_idx] == '!') {
            op_type = str[op_idx] == '=' ? 1 : -1;
            str[op_idx] = '\0';
            break;
        }
    }
    (op_type == 1 ? eq_relations : neq_relations).push_back(make_pair(
        get_word(str),
        get_word(str + (op_idx + 2))
    ));
}

int main(void)
{
    scanf("%s", S);
    S_len = strlen(S);
    
    int begin = 0;
    for (int i = 0; i <= S_len; ++i) {
        if (S[i] == '&' || S[i] == '\0') {
            S[i] = '\0';
            apply_relation(S + begin, i - begin);
            begin = i + 2;
            ++i;
        }
    }

    // EQ에 대해 모두 그룹핑
    for (auto it = eq_relations.begin(); it != eq_relations.end(); ++it) {
        Word* a = get_parent(it->first);
        Word* b = get_parent(it->second);
        if (a->len > b->len) swap(a, b);
        b->parent = a;
    }

    // 한 그룹에 2개 이상의 정수가 있으면 False
    for (auto it = words.begin(); it != words.end(); ++it) {
        Word* word = (*it);
        Word* parent = get_parent(word);
        if (word == parent) continue;
        parent->cnt_integer += word->cnt_integer;
        if (parent->cnt_integer >= 2) {
            puts("0==1");
            return 0;
        }
    }
    
    // 같은 그룹끼리의 조건을 결과에 적용
    for (auto it = words.begin(); it != words.end(); ++it) {
        Word* word = (*it);
        Word* parent = get_parent(word);
        if (word != parent) {
            strcat(R + R_len, parent->value); R_len += parent->len;
            strcat(R + R_len, "=="); R_len += 2;
            strcat(R + R_len, word->value); R_len += word->len;
            strcat(R + R_len, "&&"); R_len += 2;
        }
    }

    // NEQ에 대한 적용
    set< pair<Word*,Word*> > neq_dup_checker;
    for (auto it = neq_relations.begin(); it != neq_relations.end(); ++it) {
        Word* a = get_parent(it->first);
        Word* b = get_parent(it->second);
        if (a == b) {  // 같은 그룹끼리 다르다면 False
            puts("0==1");
            return 0;
        }
        if (a->len > b->len) swap(a, b);

        pair<Word*, Word*> wp = make_pair(a, b);  // 이미 나온 NEQ조건이라면 패스
        if (neq_dup_checker.find(wp) == neq_dup_checker.end()) {
            neq_dup_checker.insert(wp);
        } else {
            continue;
        }

        // 둘 다 정수라면 패스
        if (a->cnt_integer > 0 && b->cnt_integer > 0) continue;

        strcat(R + R_len, a->value); R_len += a->len;
        strcat(R + R_len, "!="); R_len += 2;
        strcat(R + R_len, b->value); R_len += b->len;
        strcat(R + R_len, "&&"); R_len += 2;
    }

    if (R_len == 0) {
        puts("0==0");
    } else {
        R[R_len - 2] = '\0';
        printf("%s\n", R);
    }

    return 0;
}