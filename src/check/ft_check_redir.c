/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:51:56 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:27:40 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_redir_sub(char *line, int i, int *redir)
{
	int	found;
	int	j;

	if (line[i] == '<' || line[i] == '>')
	{
		if (ft_chrcnt(&line[i], '<') > 2 || ft_chrcnt(&line[i], '>') > 2)
			*redir = 1;
		found = 0;
		j = ft_chrcnt(&line[i], '<') + ft_chrcnt(&line[i], '>');
		while (line[i + j] && line[i + j] != '<' && line[i + j] != '>')
		{
			if (line[i + j] != ' ' && line[i + j] != '|')
				found = 1;
			j++;
		}
		if (!found && !*redir)
			*redir = 2;
	}
}

void	ft_check_redir(char *line, char **env)
{
	int	redir;
	int	quote;
	int	i;

	i = -1;
	redir = 0;
	quote = 0;
	while (line[++i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (quote)
			continue ;
		ft_check_redir_sub(line, i, &redir);
	}
	if (redir == 1)
		printf("syntax error: unexpected redirection operator\n");
	else if (redir == 2)
		printf("syntax error: unknown redirection path\n");
	else
		ft_check_pipe(line, env);
}
