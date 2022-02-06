# include "../include/header.h"

char *cancel_bonus(char *str)
{
	int i;
	char *p1;
	char *p2;
	char temp;

	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&'))
			{
				str[i] = '\0';
				p1 = ft_strdup(str);
				p2 = ft_strdup(str + i + 2);
				free(str);
				str = ft_strjoin(p1, p2);
				free(p1);
				p1 = NULL;
				free(p2);
				p2 = NULL;
			}	
		}
		i++;
	}
	return (str);
}



int count_arg(char *b_cmd)
{
	int i;
	int count;
	int temp;

	count = 0;
	i = 0;
	while (b_cmd[i])
	{
		if (i > 0 && b_cmd[i - 1] && b_cmd[i - 1] == ' ' && b_cmd[i] != ' ' && b_cmd[i] != '-')
		{
			count++;
			i++;
		}
		else if (b_cmd[i] == '-')
		{
			if (b_cmd[i + 1] && b_cmd[i + 1] == '-')
			{
				i += 2;
				while (b_cmd[i] && (b_cmd[i] != '\0' && b_cmd[i] != ' ' && b_cmd[i] != '\n'))
					i++;
				count++;
			}
			else
			{
				i++;
				temp = count;
				while (b_cmd[i] && (b_cmd[i] != '\0' && b_cmd[i] != ' ' && b_cmd[i] != '\n'))
				{
					i++;
					count++;
				}
				if (count == temp)
					count++;
			}
		}
		else
			i++;
	}
	return (count);
}

char **conv_args(char *b_cmd)
{
	char **args;
	int i;
	int y;
	int start;
	char *temp;

	y = 1;
	i = 0;
	args = malloc(sizeof(char *) * (count_arg(b_cmd) + 2));
	if (args == NULL)
		return (NULL);
	while (b_cmd[i])
	{
		if (i > 0 && b_cmd[i - 1] && b_cmd[i - 1] == ' ' && b_cmd[i] != ' ' && b_cmd[i] != '-')
		{
			start = i;
			while (b_cmd[i] && (b_cmd[i] != '\0' && b_cmd[i] != ' ' && b_cmd[i] != '\n'))
				i++;
			args[y] = ft_substr(b_cmd, start, i - start);
			y++;
		}
		else if (b_cmd[i] == '-')
		{
			if (b_cmd[i + 1] && b_cmd[i + 1] == '-')
			{
				start = i;
				while (b_cmd[i] && (b_cmd[i] != '\0' && b_cmd[i] != ' ' && b_cmd[i] != '\n'))
					i++;
				args[y] = ft_substr(b_cmd, start, i - start);
				y++;
			}
			else
			{
				i++;
				while (b_cmd[i] && (b_cmd[i] != '\0' && b_cmd[i] != ' ' && b_cmd[i] != '\n'))
				{
					temp = ft_substr(b_cmd, i, 1);
					args[y] = ft_strjoin("-", temp);
					free(temp);
					temp = NULL;
					y++;
					i++;
				}
			}
		}
		else
			i++;
	}
	args[y] = NULL;
	return (args);
}
