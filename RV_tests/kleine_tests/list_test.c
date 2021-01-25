#include "minishell.h"

int main(void)
{
	t_list *list;

	list = create_elem;
	ft_list_push_back(list, "nulll");
	ft_list_push_back(list, "1");
	ft_list_push_back(list, "tweede");
	ft_list_push_back(list, "drie");

	printf("kan dit: %s?\n", list->content);

	return 0;
}
