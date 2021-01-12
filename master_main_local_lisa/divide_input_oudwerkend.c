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
		while (line[start + len] == ' ')
			start++;
		if (ft_strchr("|<>", line[start + len]))
		{
			start += len;
			while (ft_strchr("|<>", line[start + len]))
				len++;
		}
		else if (line[start + len] != 39 && line[start + len] != 34)
		{
			start += len;
			while (line[start + len] != '\0' && line[start + len] != ' ' && line[start + len] != 39 && line[start + len] != 34)
				len++;
		}
		if (line[start + len] == ' ' || line[start + len] == '\0')
			start = create_list(list, line, &len, start);
		if (line[start + len] == 39)
		{
			len++;
			while (line[start + len] != '\0' && line[start + len] != 39)
				len++;
			if (line[start + len] != 39)
				printf("write function for extra input\n");
			len++;
			start = create_list(list, line, &len, start);
		}
		if (line[start + len] == 34)
		{
			len++;
			while (line[start + len] != '\0' && line[start + len] != 34)
				len++;
			if (line[start + len] != 34)
				printf("write function for extra input\n");
			len++;
			start = create_list(list, line, &len, start);
		}
		len++;
	}
}