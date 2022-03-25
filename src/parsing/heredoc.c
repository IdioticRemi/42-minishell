/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:58 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:18:29 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_max(size_t a, size_t b)
{
	if (a < b)
		return (b);
	return (a);
}

char	*set_s(char *line, char *cmd_final, int isInquote)
{
	char	*temp;
	char	*final;
	char	*temp2;

	temp2 = NULL;
	if (isInquote == 0)
	{
		temp2 = with_var(line, NULL, NULL, 0);
		temp = ft_strjoin(temp2, "\n");
	}
	else
		temp = ft_strjoin(line, "\n");
	if (cmd_final)
		final = ft_strjoin(cmd_final, temp);
	else
		final = ft_strdup(temp);
	free(temp);
	if (temp2)
		free(temp2);
	if (cmd_final)
		free(cmd_final);
	return (final);
}

int	check_heredoc_quote(char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	cut_heredoc(char **end, int i, int *bool_quote, char **final_line)
{
	if (!end[i] && !*final_line)
		*final_line = ft_strdup("");
	if (end[i])
		*bool_quote = check_heredoc_quote(end[i]);
	else
		*bool_quote = 0;
}

char	*heredoc_c(char **end, t_cmd *stru, char *final_line)
{
	int		i;
	int		bool_quote;
	char	*line;
	char	*temp;

	i = 0;
	while (end[i])
	{
		line = readline("\033[31mHEREDOC\033[0m> ");
		if (!line)
			break ;
		temp = without_quote(end[i]);
		if (ft_strncmp(line, temp, \
			ft_max(ft_strlen(line), ft_strlen(end[i]))) == 0)
			i++;
		cut_heredoc(end, i, &bool_quote, &final_line);
		if (end[i])
			final_line = set_s(line, final_line, bool_quote);
		free(line);
		free(temp);
	}
	ft_afree((void **)end);
	stru->heredoc = 1;
	return (final_line);
}
