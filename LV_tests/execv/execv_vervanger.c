#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hallo dit is de vervangende file");
    printf("%d\n", getpid());
    return(0);
}