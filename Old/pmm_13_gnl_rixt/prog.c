#include <unistd.h>
#include <stdio.h>


int		main()
{
	int ret;
	char str[6];
	ret = read(0, str, 6);
	printf("ret = [%d]\n", ret);

	return(0);
}
