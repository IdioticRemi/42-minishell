/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/25 03:24:56 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **str, char *value)
{
	char	**final;
	int		i;

	i = -1;
	if (str == NULL)
	{
		final = (char **)malloc(sizeof(char *) * 2);
		i++;
	}
	else
	{
		while (str[++i])
			;
		final = (char **)malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (str[++i])
			final[i] = ft_strdup(str[i]);
	}
	final[i] = value;
	final[i + 1] = NULL;
	if (str)
		ft_afree((void **)str);
	return (final);
}

void	get_index_credir(char *new, int *i, char **temp, char **start)
{
	if (new[*i + 1] && (new[*i + 1] == '>' || new[*i + 1] == '<'))
		(*i)++;
	if (new[*i + 1] && new[*i + 1] != ' ')
	{
		*temp = ft_strjoin(*start, " ");
		free(*start);
		*start = *temp;
	}
	while (new[*i] && (new[*i] == '>' || new[*i] == '<' || new[*i] == ' '))
		(*i)++;
	while (new[*i] && (new[*i] != ' ' || in_quote(new, *i, 0) == 1))
		(*i)++;
	while (new[*i] && new[*i] == ' ')
		(*i)++;
}

char	*conv_redir(char *cmd)
{
	int		i;
	char	*new;
	char	*start;
	char	*end;
	char	*temp;

	i = 0;
	new = ft_strdup(cmd);
	while (new[i])
	{
		if ((new[i] == '>' || new[i] == '<') && in_quote(cmd, i, 0) == 0)
		{
			start = ft_substr(new, 0, i);
			get_index_credir(new, &i, &temp, &start);
			end = ft_substr(new, i, ft_strlen(new + i));
			free(new);
			new = ft_strjoin(start, end);
			free(start);
			free(end);
			i = 0;
		}
		i++;
	}
	return (new);
}

char	*get_next(char *cmd, int index, int heredoc)
{
	int	i;
	int	start;

	start = index + 1 + heredoc;
	if (!cmd[start])
		return (NULL);
	while (cmd[start] == ' ')
		start++;
	i = start;
	while ((cmd[i] != ' ' || in_quote(cmd, i, 0) == 1) && cmd[i] != '\0')
		i++;
	return (ft_substr(cmd, start, i - start));
}

void	cut_re(int *mode, char **path, int *i, char *cmd)
{
	free(*path);
	*path = NULL;
	if (cmd[*i + 1] && cmd[*i + 1] == '>')
	{
		*mode = 2;
		*path = get_next(cmd, *i + 1, 0);
		(*i)++;
	}
	else
	{
		*mode = 1;
		*path = get_next(cmd, *i, 0);
	}
}
