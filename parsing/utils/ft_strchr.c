# include "../include/header.h"

int ft_strchr(const char *string, int searchedChar)
{
	char	*str;
	int i;

	i = 0;
	str = (char *)string;
	while (str[i] != (char) searchedChar)
	{
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}