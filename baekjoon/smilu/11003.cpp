#include<iostream>
#include<unistd.h>
#include<sys/syscall.h>
#include<algorithm>
using namespace std;

#define MAX_BUF 1000000

char buf[MAX_BUF];
char* bp = buf + MAX_BUF;
char outbuf[MAX_BUF + 20];
char *op = outbuf;

char readByte()
{
    if(bp == buf + MAX_BUF) {
        syscall(0x00, 0, buf, MAX_BUF);
        bp = buf;
    }
    return *(bp++);
}
int readInt()
{
    int ret = 0;
    bool neg = false;
    char ch = getchar();
    if(ch == '-') neg = true;
    else ret = ch-'0';
    while('0' <= (ch=getchar()) && ch <= '9') ret = ret*10 + (ch-'0');
    return ret * (neg ? -1 : 1);
}
void printInt(int n)
{
    if(n<0) n = -n, *op++ = '-';
    char* cur = op;
    do {
        *cur++ = n % 10 + '0';
        n /= 10;
    } while(n);
    reverse(op, cur);
    *cur++ = ' ';
    if(cur < outbuf + MAX_BUF) op = cur;
    else {
        syscall(0x01, 1, outbuf, cur - outbuf);
        op = outbuf;
    }
}
void flush()
{
    syscall(0x01, 1, outbuf, op - outbuf);
    fflush(stdout);
}

pair<int,int> a[5000000];
int main()
{
    int n=readInt(), l=readInt();
    int head=0, tail=0;
    for(int i=0; i<n; ++i) {
        int tmp = readInt();
        while(head != tail && a[head].second+l <= i) ++head;
        while(head != tail && a[tail-1].first >= tmp) --tail;
        a[tail++] = {tmp, i};
        printInt(a[head].first);
    }
    flush();
    _Exit(0);
}
