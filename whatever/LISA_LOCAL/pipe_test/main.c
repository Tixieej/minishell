#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	*ft_create_fd_array(int times, int *fd_array)
{
	int			count;

	count = 0;
	fd_array = malloc(sizeof(int) * (times * 2));
	if (!fd_array)
		printf("error");
		// error_handler("malloc failed in pipes", NULL, cmd);
	while (count < times)
	{
		if (pipe(fd_array + (count * 2)) < 0)
		{
			printf("error");
			// error_handler("pipe failed", NULL, cmd);
			// free(pipe)
		}
		count++;
	}
	return (fd_array);
}

static void close_fd_array(int  *fd_array)
{
	int count;

	count = 0;
	while (fd_array[count] != '\0')
	{
		printf("fd[%d]\n", fd_array[count]);
		close(fd_array[count]);
		count++;
	}
}

// static int count_pipes(t_command *cmd)
// {
//     int times;

//     times = 1;
//     while (cur_struct)
// 	{
// 		if (cur_struct->pipe_right == 1)
// 			times++;
// 		cur_struct = cur_struct->next;
// 	}
// 	cur_struct = cmd;
//     return (times);
// }

int main(void)
{
  int status;
  int i;
  int times;
  int *pipes;
  int cmd_times;
  pid_t	process;
  int count;

  // arguments for commands; your parser would be responsible for
  // setting up arrays like these
  process = 0;
  pipes = NULL;
  cmd_times = 3;
  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", "h", NULL};
  char *cut_args[] = {"cut", "-b", "1-4", NULL};
  times = 2; // count_pipes
  pipes = ft_create_fd_array(times, pipes);

  // we now have 4 fds:
  // pipes[0] = read end of cat->grep pipe (read by grep)
  // pipes[1] = write end of cat->grep pipe (written by cat)
  // pipes[2] = read end of grep->cut pipe (read by cut)
  // pipes[3] = write end of grep->cut pipe (written by grep)

  // Note that the code in each if is basically identical, so you
  // could set up a loop to handle it.  The differences are in the
  // indicies into pipes used for the dup2 system call
  // and that the 1st and last only deal with the end of one pipe.

  // fork the first child (to execute cat)
cmd_times = 0;
count = 0;
while (cmd_times < 3)
{
	if ((process = fork()) == 0)
	{
		if (cmd_times == 0)
		{
			// replace cat's stdout with write part of 1st pipe
			// dup2(pipes[1], 1);
			dup2(pipes[count + 1], 1);
			// close all pipes (very important!); end we're using was safely copied
			close_fd_array(pipes);
			execvp(*cat_args, cat_args);
		}
		else if (cmd_times == 1)
		{
			// replace grep's stdin with read end of 1st pipe
			// dup2(pipes[0], 0);
			printf("count : %d\n", count);
			printf("times : %d\n", times);
			dup2(pipes[count - 2], 0);
		 	// replace grep's stdout with write end of 2nd pipe
			// dup2(pipes[3], 1);
			dup2(pipes[count + 1], 1);
		 	// close all ends of pipes
			close_fd_array(pipes);
			execvp(*grep_args, grep_args);
		}
		else if (cmd_times == 2)
		{
			// replace cut's stdin with input read of 2nd pipe
			printf("count : %d\n", count);
			printf("times : %d\n", times);
			// dup2(pipes[2], 0);
			dup2(pipes[count - 2], 0);
			// close all ends of pipes
			close_fd_array(pipes);
			execvp(*cut_args, cut_args);
		}	
	}
	if (process == -1)
		printf("error");
	cmd_times++;
	count += 2;
}
  // only the parent gets here and waits for 3 children to finish
  close_fd_array(pipes); // klopt die?
  for (i = 0; i < 3; i++)
	wait(&status);
	// wait(NULL);
}

// #include <stdio.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>

// #include <sys/types.h>
// #include <sys/wait.h>

// /**
//  * Executes the command "cat scores | grep Villanova | cut -b 1-10".
//  * This quick-and-dirty version does no error checking.
//  *
//  * @author Jim Glenn
//  * @version 0.1 10/4/2004
//  */

// int main(void)
// {
//   int status;
//   int i;

//   // arguments for commands; your parser would be responsible for
//   // setting up arrays like these

//   char *cat_args[] = {"cat", "scores", NULL};
//   char *grep_args[] = {"grep", "Villanova", NULL};
//   char *cut_args[] = {"cut", "-b", "1-10", NULL};

//   // make 2 pipes (cat to grep and grep to cut); each has 2 fds

//   int pipes[4];
//   pipe(pipes); // sets up 1st pipe
//   pipe(pipes + 2); // sets up 2nd pipe

//   // we now have 4 fds:
//   // pipes[0] = read end of cat->grep pipe (read by grep)
//   // pipes[1] = write end of cat->grep pipe (written by cat)
//   // pipes[2] = read end of grep->cut pipe (read by cut)
//   // pipes[3] = write end of grep->cut pipe (written by grep)

//   // Note that the code in each if is basically identical, so you
//   // could set up a loop to handle it.  The differences are in the
//   // indicies into pipes used for the dup2 system call
//   // and that the 1st and last only deal with the end of one pipe.

//   // fork the first child (to execute cat)
  
//   if (fork() == 0)
//     {
//       // replace cat's stdout with write part of 1st pipe

//       dup2(pipes[1], 1);

//       // close all pipes (very important!); end we're using was safely copied

//       close(pipes[0]);
//       close(pipes[1]);
//       close(pipes[2]);
//       close(pipes[3]);

//       execvp(*cat_args, cat_args);
//     }
//   else
//     {
//       // fork second child (to execute grep)

//       if (fork() == 0)
// 	{
// 	  // replace grep's stdin with read end of 1st pipe
	  
// 	  dup2(pipes[0], 0);

// 	  // replace grep's stdout with write end of 2nd pipe

// 	  dup2(pipes[3], 1);

// 	  // close all ends of pipes

// 	  close(pipes[0]);
// 	  close(pipes[1]);
// 	  close(pipes[2]);
// 	  close(pipes[3]);

// 	  execvp(*grep_args, grep_args);
// 	}
//       else
// 	{
// 	  // fork third child (to execute cut)

// 	  if (fork() == 0)
// 	    {
// 	      // replace cut's stdin with input read of 2nd pipe

// 	      dup2(pipes[2], 0);

// 	      // close all ends of pipes

// 	      close(pipes[0]);
// 	      close(pipes[1]);
// 	      close(pipes[2]);
// 	      close(pipes[3]);

// 	      execvp(*cut_args, cut_args);
// 	    }
// 	}
//     }
//   // only the parent gets here and waits for 3 children to finish
  
//   close(pipes[0]);
//   close(pipes[1]);
//   close(pipes[2]);
//   close(pipes[3]);

//   for (i = 0; i < 3; i++)
//     wait(&status);
//     // wait(NULL);
// }