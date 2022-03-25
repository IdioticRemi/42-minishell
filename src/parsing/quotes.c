/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:58 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:18:29 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_quote(char *cmd)
{
	int		i;
	char	*result;
	char	*start;
	char	*end;

	result = ft_strdup(cmd);
	i = 0;
	start = NULL;
	end = NULL;
	while (result[i])
	{
		if (((result[i] == '\'' && in_doublequote(cmd, i) == 0)
				|| (result[i] == '"' && in_singlequote(cmd, i) == 0)))
		{
			start = ft_substr(result, 0, i);
			end = ft_substr(result, i + 1, ft_strlen(result) - i);
			free(result);
			result = ft_own_strjoin(start, end);
			i = 0;
		}
		else
			i++;
	}
	return (result);
}

void	without_quote_thing(char **thing)
{
	char	*temp;

	temp = ft_strdup(*thing);
	free(*thing);
	*thing = without_quote(temp);
	free(temp);
}

void	without_quote_args(t_cmd *env)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (env->argv[i])
	{
		without_quote_thing(&env->argv[i]);
		i++;
	}
	if (env->out)
		without_quote_thing(&env->out);
	if (env->in)
		without_quote_thing(&env->in);
}
