#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char cur[512];
char prev[512];

void
copy(char dest[], char src[], int len) {
  int i;
  for (i = 0; i <= len; i++) {
    dest[i] = src[i];
  }
}

int
isduplicate(char a[], int alen, char b[], int blen) {
  if (alen != blen) {
    return 0;
  }
  int i;
  for (i = 0; i <= alen; i++) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

void
printline(char chars[], int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf(1, "%c", chars[i]);
    if (chars[i] == '\n') {
      break;
    } 
  }
}

void
uniq(int fd, char *name)
{
  int i, n;
  int plen;
  int ci;

  ci = plen = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      cur[ci] = buf[i];
      ci++;
      if(buf[i] == '\n') {
	if (!isduplicate(cur, ci, prev, plen)) {
          printline(cur, ci);
          plen = ci;
          copy(prev, cur, plen);
	}
        ci = 0;
      }
    }
  }
  if(n < 0){
    printf(1, "uniq: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    uniq(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[i]);
      exit();
    }
    uniq(fd, argv[i]);
    close(fd);
  }
  exit();
}
