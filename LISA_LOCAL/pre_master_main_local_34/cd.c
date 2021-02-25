/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/25 11:13:46 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*move_backwards(char *path)
{
	int len;

	len = ft_strlen(path);
	while (path[len] != '/')
	{
		len--;
	}
	return(ft_substr(path, 0, len));
}

void        *alter_env(char **env, char *var, char *file)
{
    int count;
	int	len_var;

	len_var = ft_strlen(var);
    count = 0;
    while (env[count])
    {
        if (!ft_strncmp(env[count], var, len_var))
		{
			env[count] = ft_strjoin(env[count], "/");
			env[count] = ft_strjoin(env[count], file);
		}   
        count++;
    }
    return (NULL);
}

void        cd(t_command *command, char **env, char *path)
{
	struct stat		buffer;
	int				len;
	int				start;
	char			*file;

	len = 0;
	start = 0;
	file = NULL;
	path = getcwd(NULL, 0);
	printf("path1: %s\n", path);
    if (path == NULL)
        error_handler("getcwd failure", NULL, command); //veranderen met geheugen?
	if (command->args == NULL)
	{
		path = check_env(env, "HOME=");
		if (path == NULL)
			printf("minishell: HOME= non-existing\n");
		if (chdir(path) != 0)
			printf("minishell: %s: path non-existing\n", path);
		return;
	}
	printf("content %s\n", command->args->content);
	while (command->args->content[start + len] != '\0')
	{
		while (command->args->content[start + len] != '.' && command->args->content[start + len] != '/' && command->args->content[start + len] != '\0')
			len++;
		if (len > 0)
		{
			printf("content %s\n", command->args->content);
			file = ft_substr(command->args->content, start, len);
			printf("file %s\n", file);
			{
				if (stat(file, &buffer) == 0)
				{
					alter_env(&(*env), "PWD=", file);
					path = ft_strjoin(path, "/");
					path = ft_strjoin(path, file);
					start += len;
					len = 0;
					// return;
				}
				else
				{
					printf("minishell: %s: Not a directory\n", file);
					free(file);
					return;
				}	
			}
			free(file);
			file = NULL;
		}
		if (command->args->content[len] == '.')
		{
			if (command->args->content[len + 1] == '.')
			{
				path = move_backwards(path);
				start++;
			}
			if (command->args->content[len + 1] == '/')
				command->args->content = ft_substr(command->args->content, 2, (ft_strlen(path) - 2));
		}
		// printf("content: %s", command->args->content);
		len++;
	}
	// if (command->args->content[0] == '.' && command->args->content[1] == '.')
	// 	path = move_backwards(path);   //LEAK?
	// else if (command->args->content[0] == '.' && command->args->content[1] == '/')
	// 	command->args->content = ft_substr(command->args->content, 2, (ft_strlen(path) - 2));
	// else if (stat(command->args->content, &buffer) == 0)
	// {
	// 	while (command)
	// 	{
	// 		if (stat(command->args->content, &buffer) == 0)
	// 		{
	// 			alter_env(&(*env), "PWD=", command->args->content);
	// 			path = ft_strjoin(path, "/");
	// 			path = ft_strjoin(path, command->args->content);
	// 		}
	// 		command = command->next;
	// 	}
	// }
	// else 
	// 	error_handler("file non-existing", NULL, NULL);
	// if (path)
	// 	printf("path: %s", path);
	if (chdir(path) != 0)
	{
		printf("minishell: %s: Not a directory\n", path);
		return;
	}
		
		// error_handler("path non-existing", NULL, NULL);

	// printf("path: %s", path);
	// printf("PWD 1: %s\n", get_pointer_env(env, "PATH=")); 
	// printf("PWD: %s\n", getcwd(NULL, 0));
}