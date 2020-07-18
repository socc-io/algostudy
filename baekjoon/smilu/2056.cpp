#include <bits/stdc++.h>
class FastIO {
    int fd, bufsz;
    char *buf, *cur, *end;
public:
    FastIO(int _fd = 0, int _bufsz = 1 << 20) : fd(_fd), bufsz(_bufsz) {
        buf = cur = end = new char[bufsz];
    }
    ~FastIO() {
        delete[] buf;
    }
    bool readbuf() {
        cur = buf;
        end = buf + bufsz;
        while (true) {
            size_t res = fread(cur, sizeof(char), end - cur, stdin);
            if (res == 0) break;
            cur += res;
        }
        end = cur;
        cur = buf;
        return buf != end;
    }
    int readint() {
        while (true) {
            if (cur == end) readbuf();
            if (isdigit(*cur) || *cur == '-') break;
            ++cur;
        }
        bool sign = true;
        if (*cur == '-') {
            sign = false;
            ++cur;
        }
        int ret = 0;
        while (true) {
            if (cur == end && !readbuf()) break;
            if (!isdigit(*cur)) break;
            ret = ret * 10 + (*cur - '0');
            ++cur;
        }
        return sign ? ret : -ret;
    }
};

#define INF 0x7FFFFFF0

int et[10000];

int main(void)
{
  FastIO fio;
  int n = fio.readint();
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int t = fio.readint(), c = fio.readint();
    int y = 0;
    for (int j = 0; j < c; j++) {
      int tmp = fio.readint() - 1;
      y = max(y, et[tmp]);
    }
    et[i] = y + t;
    ans = max(ans, et[i]);
  }
  printf("%d", ans);
}
