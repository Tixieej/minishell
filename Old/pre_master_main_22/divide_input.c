/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   the_og_divide_input.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD
/*   Created: 2021/03/23 15:56:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/23 15:57:03 by rixt          ########   odam.nl         */
=======
/*   Created: 2021/01/12 10:25:42 by livlamin      #+#    #+#                 */
/*   Updated: 2021/03/29 13:18:15 by rde-vrie      ########   odam.nl         */
>>>>>>> 1339ba39ddf1d9c2ed6f07addf5053e792686cd2
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD
void    prompt(void)
=======
// dit is een versie van lisa waarin echo hallo;echo doei niet werkt, maar ze heeft nu op test 23_L gezet waarin dat wel werkt
void	prompt(void)
>>>>>>> 1339ba39ddf1d9c2ed6f07addf5053e792686cd2
{
    write(2, "\033[38;5;105mminishell: \e[0m", 27);
}
<<<<<<< HEAD
static int  create_list_item(t_list **list, char *line,
                                size_t *len, unsigned int start)
{
    char    *temp;
    temp = ft_substr((char const *)line, start, *len);
    printf("%s\n", temp);
    ft_list_push_back(list, temp);
    printf("start 1: %d\n", start);
    printf("len: %zu\n", *len);
    if (line[start + *len] == ';')
    {
        ft_list_push_back(list, ft_strdup(";"));
        start++;
    }
    start += *len;
    *len = 0;
    printf("start 2: %d\n", start);
    return (start);
=======
static int	create_list_item(t_list **list, char *line,
								size_t *len, unsigned int start)
{
	char	*temp;

	temp = ft_substr((char const *)line, start, *len);
	//printf("%s\n", temp);
	ft_list_push_back(list, temp);
	//printf("start 1: %d\n", start);
	//printf("len: %zu\n", *len);
	if (line[start + *len] == ';')
	{
		ft_list_push_back(list, ft_strdup(";"));
		start++;
	}
	start += *len;
	*len = 0;
	//printf("start 2: %d\n", start);
	return (start);
>>>>>>> 1339ba39ddf1d9c2ed6f07addf5053e792686cd2
}
static int  handle_quotation_marks(t_list **list, char *line,
                                    size_t *len, unsigned int start)
{
<<<<<<< HEAD
    if (line[start + *len] == '\'')
    {
        start++;
        while (!ft_strchr("\''\0'", line[start + *len]))
            (*len)++;
        if (line[start + *len] != '\'')
            error_handler("missing quotation marks\n", *list, NULL);
        start = create_list_item(list, line, len, start + 1);
        (*len)++;
    }
    else if (line[start + *len] == '\"')
    {
        start++;
        while (!ft_strchr("\"'\0'", line[start + *len + 1]))
            (*len)++;
        if (line[start + *len + 1] != '\"')
            error_handler("missing quotation marks\n", *list, NULL);
        start++;
        start = create_list_item(list, line, len, start);
    }
    return (start + 1);
=======
	if (line[start + *len] == '\'')
	{
		start++;
		while (!ft_strchr("\''\0'", line[start + *len]))
			(*len)++;
		if (line[start + *len] != '\'')
			error_handler("missing quotation marks\n", *list, NULL);
		start = create_list_item(list, line, len, start + 1);
		(*len)++;
	}
	else if (line[start + *len] == '\"')
	{
		start++;
		while (!ft_strchr("\"'\0'", line[start + *len + 1]))
			(*len)++;
		if (line[start + *len + 1] != '\"')
			error_handler("missing quotation marks\n", *list, NULL);
		start++;
		start = create_list_item(list, line, len, start);
	}
	return (start + 1);
>>>>>>> 1339ba39ddf1d9c2ed6f07addf5053e792686cd2
}
void    divide_input(t_list **list, char *line,
                            size_t len, unsigned int start)
{
<<<<<<< HEAD
    while (line[start + len] != '\0')
    {
        while (line[start + len] == ' ')// && line[start + len] != '\0')
            start++;
        if (!ft_strchr("' ''<''>'\'\"'\0'';'", line[start + len]))
        {
            start += len;
            while (!ft_strchr("' '';''<''>' \'\"'\0'", line[start + len]))
                len++;
        }
        if (!ft_strncmp(&line[start + len], ">>>", 3))
            error_handler("error near unexpected token`>'\n", *list, NULL);
        if (ft_strchr("\'\"", line[start + len]))
            start = handle_quotation_marks(list, line, &len, start);
        if (ft_strchr("';'' ''<''>''\0'", line[start + len]))
        {
            if (len < 1 && line[start + len + 1] == '>')
                len = 2;
            if (line[start + len] == '>' || line[start + len] == '<')
                len = 1;
            if (len != 0)
                start = create_list_item(list, line, &len, start);
            printf("char: %c\n", line[start + len]);
        }
        len++;
    }
=======
	while (line[start + len] != '\0')
	{
		while (line[start + len] == ' ')// && line[start + len] != '\0')
			start++;
		if (!ft_strchr("' ''<''>'\'\"'\0'';'", line[start + len]))
		{
			start += len;
			while (!ft_strchr("' '';''<''>' \'\"'\0'", line[start + len]))
				len++;
		}
		if (!ft_strncmp(&line[start + len], ">>>", 3))
			error_handler("error near unexpected token`>'\n", *list, NULL);
		if (ft_strchr("\'\"", line[start + len]) && line[start + len] != '\0')
			start = handle_quotation_marks(list, line, &len, start);
		if (ft_strchr("';'' ''<''>''\0'", line[start + len]))
		{
			if (line[start + len] == '>' && line[start + len + 1] == '>') // len < 1 && 
			{
				start++;
				len = 2;
			}
			if (line[start + len] == '>' || line[start + len] == '<')
				start++;	
			if (len != 0)
				start = create_list_item(list, line, &len, start);
			//printf("char: %c\n", line[start + len]);
		}
		len++;
	}
>>>>>>> 1339ba39ddf1d9c2ed6f07addf5053e792686cd2
}
