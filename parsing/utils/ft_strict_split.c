#include "../include/header.h"

static int	count_word(const char *str, char *charset, int start)
{
	int	i;
	int y;
	int count;

	i = start;
	count = 0;
	while (str[i])
	{
		y = 0;
		while (charset[y])
		{
			if (charset[y] != str[i])
				break;
			y++;
			i++;
			if (!charset[y])
			{
				count++;
				i--;
			}
		}
		i++;
	}
	return (count);
}

static int split_str(const char *str, char *charset, int start, char **split)
{
	int	i;
	int y;
	int j;
	int start_d;

	j = 0;
	start_d = 0;
	i = start;
	while (str[i])
	{
		y = 0;
		while (charset[y])
		{
			if (charset[y] != str[i])
				break;
			y++;
			i++;
			if (!charset[y])
			{
				split[j] = ft_substr(str, start_d, (i - y) - start_d);
				j++;
				start_d = i;
				i--;
			}
		}
		i++;
	}
	split[j] = ft_substr(str, start_d, i - start);
	split[j + 1] = NULL;
	return (0);
}

char	**ft_stict_split(char *str, char *charset)
{
	char	**split;
	int		i;

	i = 0;
	while (str[i] && charset[i])
	{
		if (charset[i] != str[i])
		{
			i = 0;
			break;
		}
		i++;
	}
	if (count_word(str, charset, i) == 0)
	{
		split = malloc(sizeof(char *) + 1);
		if (split == NULL)
			return (NULL);
		split[0] = str;
		split[1] = NULL;
		return (split);
	}
	split = malloc(((count_word(str, charset, i)) + 1) * sizeof(char *) + 1);
	if (split == NULL)
		return (NULL);
	split_str(str, charset, i, split);
	return (split);
}
