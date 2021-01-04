#include <stdio.h> 
#include <errno.h> 
#include <string.h>
 
int main() 
{ 
    // If a file is opened which does not exist, 
    // then it will be an error and corresponding 
    // errno value will be set 
    FILE * fp;
	FILE * fd; 
  
    printf("opening a file which does not exist.\n");
    fp = fopen("GeeksForGeeks.txt", "r"); 
    printf("Value of errno: %d\n", errno); 
	printf("Error: %s\n", strerror(errno));

    printf("opening a file without access.\n");
 	fd = fopen("no_access", "r");
	printf("Value of errno: %d\n", errno);
	printf("Error: %s\n", strerror(errno));
    return 0; 
} 
