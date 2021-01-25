// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   parse.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: rdvrie <marvin@codam.nl>                     +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2021/12/01 10:25:42 by rixt          #+#    #+#                 */
// /*   Updated: 2021/01/12 17:43:39 by livlamin      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void		ft_make_struct(t_list *list, t_command *cmd)
// {
// 	cmd->program = list[0].content;
// 	cmd->args = list_to_array(list);
// 	printf("struct: %s, args[1]: %s args[2]: %s\n", cmd->program, cmd->args[1], cmd->args[2]);
// }

// char		**list_to_array(t_list *list)
// {
// 	int		count;
// 	char	**array;
// 	int		i;
// 	t_list	*begin;

// 	begin = list;
// 	count = 0;
// 	while (list) // misschien met list lopen maar dan met de kopie begin;
// 	{
// 		list = list->next; //
// 		count++; //
// 	}
// 	array = (char **)malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	list = begin;
// 	while (i < count)
// 	{
// 		array[i] = (char *)list->content;
// 		list = list->next;
// 		i++;
// 	}
// 	array[i] = NULL;
// 	return (array);
// }

// void		ft_exec(char *path, t_command cp_command, char **envp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 		execve(path, cp_command.args, envp);
// 	else
// 		wait(NULL);
// }

// void		non_buildin(t_list *list, char **envp)
// {
// 	char			**paths;
// 	char			*path;
// 	struct stat		buffer;
// 	t_command		cp_command;
// 	int				i;

// 	ft_make_struct(list, &cp_command);
// 	if (ft_strchr(cp_command.program, '/') != 0)
// 	{
// 		path = cp_command.program;
// 		paths = ft_split(path, ' ');
// 		if (stat(path, &buffer) == 0)
// 			ft_exec(path, cp_command, envp);
// 		else
// 			printf("no such file or directory: %s\n", cp_command.program);
// 	}
// 	else
// 	{
// 		paths = make_path_array(envp);
// 		i = 0;
// 		while (paths[i])
// 		{
// 			path = ft_strjoin(paths[i], "/");
// 			path = ft_strjoin(path, cp_command.program);
// 			cp_command.args[0] = path;
// 			printf("%s\n", cp_command.args[0]);
// 			if (stat(path, &buffer) == 0)
// 			{
// 				ft_exec(path, cp_command, envp);
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (stat(path, &buffer) != 0)
// 			printf("command not found: %s\n", cp_command.program);
// 	}
// }
