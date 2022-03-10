/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:58 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:18:29 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (i > 0 && b_cmd[i - 1] && (b_cmd[i - 1] == ' ' && in_quote(b_cmd, i - 1) == 0) && b_cmd[i] != ' ' && b_cmd[i] != '-')
		{
			start = i;
			while (b_cmd[i] && (b_cmd[i] != '\0' && (b_cmd[i] != ' ' || in_quote(b_cmd, i) == 1) && b_cmd[i] != '\n'))
				i++;
			args[y] = ft_substr(b_cmd, start, i - start);
			y++;
		}
		else if (b_cmd[i] == '-' && in_quote(b_cmd, i) == 0)
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
