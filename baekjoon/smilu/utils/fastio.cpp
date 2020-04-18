#include <sys/stat.h>
#include <sys/mman.h>
class fio {
  size_t rsize;
  unsigned char* rbuf;
  int ridx;

  public:
  fio() : ridx(0) {
    struct stat rstat;
    fstat(0, &rstat);
    rsize = rstat.st_size;
    rbuf = (unsigned char*)mmap(0,rsize,PROT_READ,MAP_FILE|MAP_PRIVATE,0,0);
  }

  inline bool isBlank() {
    return
      rbuf[ridx] == '\n' || rbuf[ridx] == '\t' || rbuf[ridx] == '\r' ||
      rbuf[ridx] == '\f' || rbuf[ridx] == '\v' || rbuf[ridx] == ' ';
  }
  inline void consumeBlank() { while (isBlank()) ridx++; }

  inline int readInt(){
    int res = 0, flag = 0;
    consumeBlank();
    if (rbuf[ridx] == '-'){
      flag = 1;
      ridx++;
    }
    while (!isBlank() && ridx < rsize)
      res = 10 * res + rbuf[ridx++] - '0';
    return flag ? -res : res;
  }
}io;

//x = io.readInt();