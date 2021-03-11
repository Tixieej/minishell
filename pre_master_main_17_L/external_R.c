/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   external_R.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rdvrie <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
/*   Updated: 2021/02/23 13:41:53 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_exec(char *path, t_command cmd, char **env, pid_t process)
{
	char	**args;
	t_list	*arglist;
	t_list	*new_elem;

	arglist = cmd.args;
	new_elem = ft_create_elem(path);
	if (!new_elem) //check of malloc gelukt is
		error_handler("malloc failed", NULL, &cmd);
	ft_lstadd_front(&arglist, new_elem);
	args = list_to_array(&arglist);
	printf("\tthe process id is now [%d]\n", process);
	if (process == -1)
	{
		printf(" ft_exec: forken hieronder!\n");
		process = fork();
	}
	if (process == 0)
	{
		if (execve(path, args, env) == -1)
		{
			ft_free(args);
			free(new_elem);
			exit(1);
		}
	}
	else
	{
		wait(NULL);
		ft_free(args);
		free(new_elem);
	}
}

static void	with_path(t_command cmd, char **env, pid_t process)
{
	struct stat		buffer;
	char			*path;

	path = cmd.program;
	if (stat(path, &buffer) == 0)
		ft_exec(path, cmd, env, process);
	else
		printf("no such file or directory: %s\n", cmd.program);
}

static void	attach_path(t_command cmd, char **env, pid_t process)
{
	char		**paths;
	char		*path;
	struct stat	buffer;
	int			i;

	paths = make_path_array(env);
	i = 0;
	if (paths == NULL) // dit kan mooier. misschien naar de errorfunctie sluizen?
	{
		printf("command not found: %s\n", cmd.program);
		return ;
	}
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd.program);
		//cmd.args[0] = path;
		if (stat(path, &buffer) == 0)
		{
			ft_exec(path, cmd, env, process);
			ft_free(paths);
			return ;
		}
		i++;
	}
	if (stat(path, &buffer) != 0)
		printf("command not found: %s\n", cmd.program);
	ft_free(paths);
}

void	external(t_command *cmd, char **env, pid_t process)
{
	int		stdout_fd;
	//int		stdin_fd;

	/**/ //stukje lisa als je de dup aan zou willen houden /**/
	//stdout_fd = cmd->fd_out;     
	//(void)out_fd;

	/**/ //stukje RIXT als je terug wilt naar de oude versie/**/
	stdout_fd = out_redirect(cmd); // deze had jij ungecomment;
	//stdin_fd = in_redirect(cmd, cmd->fd_in);
	if (ft_strchr(cmd->program, '/') != 0)
	{
		with_path(*cmd, env, process);
	}
	else
	{
		attach_path(*cmd, env, process);
	}
	if (dup2(stdout_fd, STDOUT_FILENO) < 0)// dit alleen uitvoeren als er redirections zijn?
	{//dit zet stdout backup weer terug
		printf("Unable to duplicate file descriptor.");
		//exit(EXIT_FAILURE); exiten stopt heel minishell, dus hier komt iets anders
	}
	// if (dup2( stdin_fd, STDIN_FILENO) < 0)
	// {
	// 	printf("Unable to duplicate file descriptor.");
	// 	exit(EXIT_FAILURE);
	// }
		//close fds?
}
