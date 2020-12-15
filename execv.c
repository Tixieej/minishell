#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("dit is het originele programma");
    printf("%d\n", getpid());
    // char *args[] = {"./execv_vervanger", NULL};
    // execv(args[0], args);
    execv("./execv_vervanger", NULL);
    return (0);
}