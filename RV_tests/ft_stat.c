/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stat.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rixt <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 15:03:30 by rixt          #+#    #+#                 */
/*   Updated: 2021/01/07 15:19:33 by rixt          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* stat kijkt of een path/file bestaat
** wat returnt het? hoe sturen we iets mee?
*/

#include <sys/stat.h>
#include <stdio.h>

int		main(void)
{
	int		ret;
	struct stat buffer;
	const char *path = "/bin/cp";
	const char *wrong = "/usr/bin/cp/onzin";
	
	ret = stat(path, &buffer);
	if (ret == 0)
		printf("pad bestaat\n");
	else
		printf("ret = %i\n", ret);
	
	ret = stat(wrong, &buffer);
	if (ret == 0)
		printf("pad bestaat\n");
	else
		printf("ret = %i\n", ret);
	return (0);
}
