#include <stdio.h>

void		array_printer(char **array)
{
	int		i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}

void			print_list(t_list *list)
{
	while (list)
	{
		printf("[%s]-\n", list->content);
		list = list->next;
	}

}
