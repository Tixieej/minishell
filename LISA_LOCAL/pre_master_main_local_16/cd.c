/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <livlamin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 13:12:48 by livlamin      #+#    #+#                 */
/*   Updated: 2021/02/04 14:54:14 by livlamin      ########   odam.nl         */
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

char        *check_env2(char **env, char *var)
{
    int count;
	int	len_var;

	len_var = ft_strlen(var);
    count = 0;
    while (env[count])
    {
        if (!ft_strncmp(env[count], var, len_var))
			return(&env[count]);
			// return(ft_strdup(&env[count][len_var]));     
        count++;
    }
    return (NULL);
}

void        cd(t_command *command, char **env)
{
    char			*path;
	struct stat		buffer;

    path = getcwd(NULL, 0);
    if (path == NULL)
        error_handler("pwd failure", NULL, NULL); //veranderen met geheugen;
	if (command->args == NULL)
	{
		path = check_env(env, "HOME=");
		if (chdir(path) != 0)
			error_handler("path non-existing", NULL, NULL);
		return;
	}
	if (path == NULL)
		error_handler("HOME= non-existing", NULL, NULL);
	if (command->args->content[0] == '.' && command->args->content[1] == '.')
		path = move_backwards(path);   //LEAK?
	else if (command->args->content[0] == '.' && command->args->content[1] == '/')
		command->args->content = ft_substr(command->args->content, 2, (ft_strlen(path) - 2));
	else if (stat(command->args->content, &buffer) == 0)
	{
		while (command)
		{
			if (stat(command->args->content, &buffer) == 0)
			{
				alter_env(&(*env), "PWD=", command->args->content);
				path = ft_strjoin(path, "/");
				path = ft_strjoin(path, command->args->content);
			}
			command = command->next;
		}
	}
	else 
		error_handler("file non-existing", NULL, NULL);
	if (chdir(path) != 0)
		error_handler("path non-existing", NULL, NULL);
	// printf("path: %s", path);
	printf("PWD: %s\n", check_env(env, "PWD="));
}