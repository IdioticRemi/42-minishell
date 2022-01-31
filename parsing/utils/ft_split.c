#include "../include/header.h"

int	check_char(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	count_word(char *str, char *charset)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (check_char(str[i], charset) == 0 && \
		check_char(str[i + 1], charset) == 1)
			result++;
		i++;
	}
	return (result);
}

void	copy_word(char *dest, char *str, char *charset)
{
	int	i;

	i = 0;
	while (check_char(str[i], charset) == 0)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

void	split_words(char *charset, char *str, char **splited)
{
	int	i;
	int	k;
	int	count_word;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (check_char(str[i], charset) == 1)
		{
			i++;
			continue ;
		}
		count_word = 0;
		while (check_char(str[i + count_word], charset) == 0)
			count_word++;
		splited[k] = malloc(sizeof(char) * (count_word + 1));
		copy_word(splited[k], str + i, charset);
		k++;
		i += count_word;
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**split;

	split = malloc(sizeof(char *) * (count_word(str, charset) + 1));
	split[count_word(str, charset)] = 0;
	split_words(charset, str, split);
	return (split);
}
