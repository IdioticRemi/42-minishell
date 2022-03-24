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

int	count_arg(char *b_cmd, int i)
{
	int	count;

	count = 0;
	while (b_cmd[i])
	{
		if (i > 0 && b_cmd[i - 1] && (b_cmd[i - 1] == ' '
				&& in_quote(b_cmd, i - 1, 0) == 0) && b_cmd[i] != ' '
			&& b_cmd[i] != '-')
		{
			count++;
			i++;
		}
		else if (b_cmd[i] == '-' && in_quote(b_cmd, i, 0) == 0)
		{
			i++;
			while (b_cmd[i] && (b_cmd[i] != '\0'
					&& b_cmd[i] != ' ' && b_cmd[i] != '\n'))
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

int	arg_check(char *b_cmd, int i)
{
	if ((i > 0 && b_cmd[i - 1] && (b_cmd[i - 1] == ' '
				&& in_quote(b_cmd, i - 1, 0) == 0)
			&& b_cmd[i] != ' ' && b_cmd[i] != '-'))
		return (1);
	return (0);
}

int	arg_tirret(char *b_cmd, int i)
{
	if (b_cmd[i] == '-' && in_quote(b_cmd, i, 0) == 0)
		return (1);
	return (0);
}

char	**conv_args(char *b_cmd)
{
	char	**args;
	int		i;
	int		y;
	int		start;

	y = 1;
	i = 0;
	args = malloc(sizeof(char *) * (count_arg(b_cmd, 0) + 2));
	while (b_cmd[i])
	{
		if (arg_check(b_cmd, i) == 1 || arg_tirret(b_cmd, i) == 1)
		{
			start = i;
			while (b_cmd[i] && (b_cmd[i] != '\0' && (b_cmd[i] != ' ' || \
				in_quote(b_cmd, i, 0) == 1) && b_cmd[i] != '\n'))
				i++;
			args[y] = ft_substr(b_cmd, start, i - start);
			y++;
		}
		else
			i++;
	}
	args[y] = NULL;
	return (args);
}
