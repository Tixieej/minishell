/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/11 08:08:00 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/11 12:48:11 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int		main(void)
{
	int			fildes[2];
	const int	BSIZE = 100;
	char		buf[BSIZE];
	ssize_t		nbytes;
	int			status;
	int			forkret;

	//fildes[0] = open("testfile", O_NONBLOCK);
	//fildes[1] = open("kopietje", O_NONBLOCK);

	//write(fildes[1], "Hello rixt\n", 11);

	//printf("fd0 = %i, fd1 = %i\n", fildes[0], fildes[1]);
	status = pipe(fildes);
	if (status == -1 )
	{
		printf("foutje\n");   /* an error occurred */
	}	
	
	forkret = fork();
	{
		if (forkret < 0) /* Handle error */
		{
			printf("-1 geforkt\n");
		}
		else if (forkret == 0)  /* Child - reads from pipe */
		{
			printf("child reads\n");
			close(fildes[1]);                       /* Write end is unused */
			nbytes = read(fildes[0], buf, BSIZE);   /* Get data from pipe */
			/* At this point, a further read would see end of file ... */
			close(fildes[0]);                       /* Finished with pipe */
			buf[nbytes] = '\0';
			printf("gelezen: %s\n", buf);
			exit(EXIT_SUCCESS);
		}
		else /* Parent - writes to pipe */
		{
			printf("parent writes\n");
			close(fildes[0]);                       /* Read end is unused */
			write(fildes[1], "hoi\n", 4);			/* Write data on pipe */
			close(fildes[1]);                       /* Child will see EOF */
    		exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

