#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char cur[512];
char prev[512];

void
uniq(int fd, char *name, int iscount, int isduplicate, int iscase)
{
  int i, n;
  int plen;
  int ci;
  int count, isfirst;

  ci = plen = 0;
  count = 0;
  isfirst = 1;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      cur[ci] = buf[i];
      if (iscase > 0 && cur[ci] >= 'A' && cur[ci] <= 'Z') {
        cur[ci] = cur[ci] - 'A' + 'a';
      }
      ci++;
      if(buf[i] == '\n') {
	if (strcmp(cur, prev)) {  // not equal
          if (isfirst) {
            isfirst = 0;
 	  } else if (iscount) {
            printf(1, "%d %s", count, prev);
          } else if (isduplicate) {
            if (count > 1) {
              printf(1, "%s", prev);
            }
          } else {
            printf(1, "%s", prev);
          }
          plen = ci;
          memmove(prev, cur, plen);
          count = 1;
	} else {
          count++;
        }
        ci = 0;
      }
    }
  }

  if (isfirst) {
    isfirst = 0;
  } else if (iscount) {
    printf(1, "%d %s", count, prev);
  } else if (isduplicate) {
    if (count > 1) {
      printf(1, "%s", prev);
    }
  } else {
    printf(1, "%s", prev);
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
    uniq(0, "", 0, 0, 0);
    exit();
  }

  int iscount, isduplicate, iscase;
  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    switch (argv[i][1]) {
      case 'c':
        iscount = 1;
        break;
      case 'd':
        isduplicate = 1;
        break;
      case 'i':
        iscase = 1;
        break;
      default:
        printf(1, "uniq: invalid flag %s", argv[i]);
        exit();
    }
  } 

  for(; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "uniq: cannot open %s\n", argv[i]);
      exit();
    }
    uniq(fd, argv[i], iscount, isduplicate, iscase);
    close(fd);
  }
  exit();
}
