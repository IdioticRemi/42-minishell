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

int	get_next_space(char *cmd, int index)
{
	int	i;

	i = index;
	while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '?'
		&& cmd[i] != '$' && cmd[i] != '"' && cmd[i] != '\'')
		i++;
	return (i);
}

char	*ft_own_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;

	if (!s1 && !s2)
		return (ft_strdup("  "));
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	ft_memcpy(result, s1, ft_strlen((char *)s1));
	ft_memcpy(result + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (result);
}

char	*get_first_quotes(char *cmd_b)
{
	int	i;

	i = 0;
	while (cmd_b[i] && cmd_b[i] != ' ' && cmd_b[i] != '\n'
		&& in_quote(cmd_b, i, 1) == 0)
		i++;
	return (ft_substr(cmd_b, 0, i));
}

void	cut_var(char *brut, int i, char **result, char **tempEnd)
{
	*tempEnd = ft_substr(*result, get_next_space(*result, \
		i + 1), ft_strlen(*result) - get_next_space(*result, i));
	free(*result);
	*result = get_first_quotes(brut + i + 1);
}

char	*with_var(char *brut, char *tempStart, char *tempEnd, int i)
{
	char	*result;
	char	*temp_result;

	result = ft_strdup(brut);
	while (result[i])
	{
		if (check_is_var(result, i) == 1)
		{
			set_start(&result, i, &tempStart);
			if (result[i + 1] == '?')
			{
				temp_result = ft_own_strjoin(tempStart,
						ft_itoa(g_shell->status));
				set_temp_end(&result, i, &tempEnd);
			}
			else
			{
				cut_var(brut, i, &result, &tempEnd);
				set_temp_result(&result, &tempStart, &temp_result);
			}
			rest_while(&tempEnd, &i, &result, &temp_result);
		}
		i++;
	}
	return (result);
}
