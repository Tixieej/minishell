/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2020/11/26 15:55:26 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <stdio.h> //
#include <unistd.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
// #include "ft_list.h"
#include <string.h>

// Names of environment variables are case-sensitive and must not contain the character ‘=’. 
//System-defined environment variables are invariably uppercase. 
// The values of environment variables can be anything that can be represented as a string.
//A value must not contain an embedded null character, since this is assumed to terminate the string. 
void	prompt()
{
	write(1, "\033[38;5;105mhallo: \e[0m", 23);
}

void	divide_input(t_list *list, char *line)
{
	size_t			len;
	unsigned int	start;
	char			*temp;

	len = 0;
	start = 0;
	temp = NULL;
	while (line[start + len] != '\0')
	{
		if (line[start + len] == 34)
		{
			len++;
			// printf("LINE: %c\n", line[start + len]);
			if (line[start + len] == 34)
			{
				temp = ft_substr((char const *)line, start, len);
				printf("%s", temp);
				// char	*ft_substr(char const *s, unsigned int start, size_t len)
				ft_list_push_back(&list, temp);
				start = len++;
				// free(temp);
				// temp = NULL;
				break;
			}
			if (line[start + len] == '\0')
			{
				printf("error"); //korter break combineren
				break;
			}
		}
		len++;
	}

}

void	read_input(t_list *list)
{
	int 	result;
	char	*line;

	result = 1;
	line = NULL;
	while (result == 1)  // voorbeelde cat > test.txt
	{
		prompt();
		result = get_next_line(0, &line);
		divide_input(list, line);
		// ft_list_push_back(&list, line);
		free(line);
		line = NULL;
	}
	// if (ft_strncmp((const char *)list->data , "cat", 3) == 0)
	// 	printf("cat type 1\n");
	// while (list)
	// {
	// 	printf("%s\n", (char*)list->data);
	// 	printf("%p\n", (char*)list->next);
	// 	list = list->next;
	// }
}

// void	child_process(t_list *list)
// {
// 	ret_value = fork();
// 	if (ret_value < 0)
// 		printf("creating childprocess had failed\n"); //
// 	else if (ret_value == 0)
// 	{
// 		// ret_value = fork();
// 		printf("ret_value2 %d\n", ret_value);
// 		printf("Child Process\n");
// 		printf("%s\n", argv[1]); //
// 		if (send_signal(ret_value) == 0)
// 			printf("childprocess is killed\n");
// 	}
// }

void compare_input(t_list *list, char **env)
{
	while (list)
	{
		if (ft_strncmp((const char *)list->data , "cat", 3) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)list->data , "cp", 2) == 0)
			printf("cat type\n");
		if (ft_strncmp((const char *)list->data , "echo", 4) == 0)
			printf("cat type\n");
	}
}

int		main(int argc, char **argv, char **env)
{
	t_list *list;
	
	list = NULL;
	(void)argv;
	if (argc != 1)
	{
		printf("no arguments needed"); //
		return (0);
	}
	read_input(list);
	if (ft_strncmp("cat" , "cat", 3) == 0)
			printf("cat type\n");
	// compare_input(list, env); //check welke type het is
	//start chilproces?
	return (0);
}
