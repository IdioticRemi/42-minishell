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

int	check_is_var(char *result, int i)
{
	if (result[i] == '$' && in_quote(result, i, 1) == 0
		&& result[i + 1] && result[i + 1] != ' ')
		return (1);
	return (0);
}

void	set_start(char **result, int i, char **tempStart)
{
	if (i > 0)
		*tempStart = ft_substr(*result, 0, i);
}

void	rest_while(char **tempEnd, int *i, char **result, char **tempResult)
{
	free(*result);
	*i = ft_strlen(*tempResult) - 1;
	*result = ft_own_strjoin(*tempResult, *tempEnd);
}

void	set_temp_end(char **result, int i, char **tempEnd)
{
	*tempEnd = ft_substr(*result, get_next_space(*result, i + 1) + 1,
			ft_strlen(*result) - (get_next_space(*result, i + 1) + 1));
}

void	set_temp_result(char **result, char **tempStart, char **tempResult)
{
	*tempResult = ft_own_strjoin(*tempStart,
			ft_get_env(g_shell->env, *result));
}
