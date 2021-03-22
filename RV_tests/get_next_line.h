/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rde-vrie <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/03 16:42:29 by rde-vrie      #+#    #+#                 */
/*   Updated: 2021/01/05 15:30:16 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int		get_next_line(int fd, char **line);
void	shift_buffer(char *buffer, int n);
int		read_till_end(int fd, char **line, char *buffer, int *ret);
size_t	ft_strlen(char *str);
char	*gnl_strcpy(char *join, char *s1, char *s2);
char	*gnl_strjoin(char *s1, char *s2, int n);
int		gnl_strchr(char *s, char c);

#endif
