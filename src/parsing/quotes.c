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
	int		j;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (((cmd[i] == '\'' && in_doublequote(cmd, i) == 0)
				|| (cmd[i] == '"' && in_singlequote(cmd, i) == 0)))
		{
			i++;
			continue ;
		}
		result[j] = cmd[i];
		j++;
		i++;
	}
	result[j] = '\0';
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

int	ft_open(int mode, char *path)
{
	int	is_open;

	if (mode == 2)
		is_open = open(path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		is_open = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	return (is_open);
}
