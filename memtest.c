#include "types.h"
#include "user.h"

#define PGSIZE 4096

int main(int argc, char **argv) {
    char *buf = sbrk(PGSIZE*10);
    buf[5*PGSIZE] = 'X';
    buf[0] = 'Y';
    fork();
    exit();
}
