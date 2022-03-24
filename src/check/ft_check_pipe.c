/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:06:52 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 16:37:12 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle(char *line, int hpipe)
{
	t_cmd	*cmd;

	if (hpipe == 1)
		printf("syntax error: unexpected pipe operator\n");
	else if (hpipe == 2)
		printf("syntax error: unexpected end of line\n");
	else
	{
		cmd = parsing(line);
		free(line);
		ft_exec(cmd);
	}
}

static void	ft_check_pipe_sub(char *line, int i, int *hpipe)
{
	int	found;
	int	j;

	if (line[i] == '|')
	{
		if (ft_chrcnt(&line[i], '|') > 1)
			*hpipe = 1;
		found = 0;
		j = 1;
		while (line[i + j])
		{
			if (!ft_strchr("> <|", line[i + j]))
				found = 1;
			j++;
		}
		if (!found && !*hpipe)
			*hpipe = 2;
	}
}

void	ft_check_pipe(char *line)
{
	int	quote;
	int	hpipe;
	int	i;

	i = -1;
	quote = 0;
	hpipe = 0;
	while (line[++i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (quote)
			continue ;
		ft_check_pipe_sub(line, i, &hpipe);
	}
	ft_handle(line, hpipe);
}
