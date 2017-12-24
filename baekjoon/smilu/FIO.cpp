#include<bits/stdc++.h>
#define MAXLEN 100000

char out_buf[MAXLEN + 20];
char *op = out_buf;

int readInt()
{
    int ret = 0;
    bool neg = false;
    char ch = getchar_unlocked();
    if(ch == '-') neg = true;
    else ret = ch - '0';
    while('0' <= (ch = getchar()) && ch <= '9')
        ret = ret*10 + (ch-'0');
    return ret * (neg ? -1 : 1);
}
void printInt(int val)
{
    if(val < 0) val = -val, *(op++) = '-';
    char *end = op;
    do {
        *(end++) = val%10;
        val /= 10;
    } while (val);
    std::reverse(op, end);
    if(end >= out_buf + MAXLEN) {
        *end = 0;
        printf("%s", out_buf);
        op = out_buf;
    } else op = end;
}
void flush()
{
    *op = 0;
    printf("%s", out_buf);
    op = out_buf;
}

int main()
{
    int a = readInt(), b = readInt();
    printInt(a+b);
    flush();
}
