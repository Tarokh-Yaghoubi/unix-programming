
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
    printf("hello from process ID %ld\n", (long)getpid());
    exit(0);
}

