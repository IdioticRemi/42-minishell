/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:51:56 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:27:33 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_quotes(char *line, char **env)
{
	int	quote;
	int	i;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
	}
	if (quote)
		printf("syntax error: unexpected end of line\n");
	else
		ft_check_redir(line, env);
}
