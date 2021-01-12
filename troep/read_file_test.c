
// void	divide_input(t_list *list, char *line)
// {
// 	size_t			len;
// 	unsigned int	start;
// 	char			*temp;

// 	len = 0;
// 	start = 0;
// 	temp = NULL;
// 	while (line[start + len] != '\0')
// 	{
// 		while (line[start + len] == ' ')
// 			start++;
// 		while (line[start + len] != ' ' && line[start + len] != 39 && line[start + len + 1] != 34)
// 			len++;
// 		if (len > 0)
// 		{
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		if (line[start + len] == 39)
// 		{
// 			start += len;
// 			len = 1;
// 			while (line[start + len] != '\0' && line[start + len] != 39)
// 				len++;
// 			if (line[start + len + 1] != 39)
// 				printf("write function for extra input\n");
// 			len++;
// 		}
// 		if (line[start + len] == 34)
// 		{
// 			start += len;
// 			len = 1;
// 			while (line[start + len] != '\0' && line[start + len] != 34)
// 				len++;
// 			if (line[start + len + 1] != 34)
// 				printf("write function for extra input\n");
// 			len++;
// 		}
// 		if (len > 0)
// 		{
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		if (line[start + len] == 34 || line[start + len] == 39)
// 			len++;
// 		len++;
// 	}
	// if (len > 0)
	// 	start = create_list(list, line, len, start);
// }

// void	divide_input(t_list *list, char *line)
// {
// 	size_t			len;
// 	unsigned int	start;
// 	char			*temp;

// 	len = 0;
// 	start = 0;
// 	temp = NULL;
// 	while (line[start + len] != '\0')
// 	{
// 		if (line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
// 		{
// 			start += len;
// 			if (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
// 				while (line[start + len] == '>' || line[start + len] == '<' || line[start + len] == '|')
// 					len++;
// 			else
// 				while (line[start + len] != '\0' && line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
// 					len++;
// 			if (line[start + len] == ' ' || line[start + len] == '\0')
// 			{
// 				start = create_list(list, line, len, start);
// 				len = 0;
// 			}
// 		}
// 		if (line[start + len] == 39)
// 		{
// 			if (line[start + len - 1] == ' ')
// 			{
// 				start += len;
// 				len = 1;
// 			}
// 			while (line[start + len] != '\0' && line[start + len] != 39)
// 				len++;
// 			if (line[start + len] != 39)
// 				printf("write function for extra input\n");
// 			len++;
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		if (line[start + len] == 34)
// 		{
// 			if (line[start + len - 1] == ' ')
// 				start += len;
// 			len = 1;
// 			while (line[start + len] != '\0' && line[start + len] != 34)
// 				len++;
// 			if (line[start + len] != 34)
// 				printf("write function for extra input\n");
// 			len++;
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		len++;
// 	}
// 	// if (len > 0)
// 	// 	start = create_list(list, line, len, start);
// }

// void	divide_input(t_list *list, char *line)
// {
// 	size_t			len;
// 	unsigned int	start;
// 	char			*temp;

// 	len = 0;
// 	start = 0;
// 	temp = NULL;
// 	while (line[start + len] != '\0')
// 	{
// 		while (line[start + len] == ' ')
// 			start++;
// 		if (line[start + len] == 34)
// 		{
// 			start += len + 1;
// 			len = 0;
// 			printf("%c\n", line[start + len]);
// 			while (line[start + len] != '\0' && line[start + len] != 34)
// 				len++;
// 			printf("%c\n", line[start + len]);
// 		}
// 		if (line[start + len] == 39)
// 		{
// 			start += len + 1;
// 			len = 0;
// 			while (line[start + len] != '\0' && line[start + len] != 39)
// 				len++;
// 		}
// 		while (line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
// 			len++;
// 		if (len > 0)
// 		{
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		len++;
// 	}
// }


// void	divide_input(t_list *list, char *line)
// {
// 	size_t			len;
// 	unsigned int	start;
// 	char			*temp;

// 	len = 0;
// 	start = 0;
// 	temp = NULL;
// 	while (line[start + len] != '\0')
// 	{
// 		if (line[start + len] == 39)
// 		{
// 			start += len + 1;
// 			len = 1;
// 			while (line[start + len] != '\0')
// 			{
// 				if (line[start + len] == 39)
// 				{
// 					start = create_list(list, line, len, start);
// 					len = 0;
// 					break;
// 				}
// 				len++;
// 			}
// 		}
// 		if (line[start + len] == 34)
// 		{
// 			start += len + 1;
// 			len = 1;
// 			while (line[start + len] != '\0')
// 			{
// 				if (line[start + len] == 34)
// 				{
// 					start = create_list(list, line, len, start);
// 					len = 0;
// 					break;
// 				}
// 				len++;
// 			}
// 		}
// 		if (line[start + len] == ' ')
// 		{
// 			start = create_list(list, line, len, start);
// 			len = 0;
// 		}
// 		len++;
// 	}
// }