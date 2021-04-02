/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   the_og_divide_input.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 15:56:58 by rixt          #+#    #+#                 */
/*   Updated: 2021/03/23 15:57:03 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    prompt(void)
{
    write(2, "\033[38;5;105mminishell: \e[0m", 27);
}
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
}
static int  handle_quotation_marks(t_list **list, char *line,
                                    size_t *len, unsigned int start)
{
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
}
void    divide_input(t_list **list, char *line,
                            size_t len, unsigned int start)
{
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
}
