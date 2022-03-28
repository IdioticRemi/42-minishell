/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:14:21 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/25 03:24:39 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_re(char *cmd, t_cmd *stru, char *path, int mode)
{
	int	i;
	int	is_open;

	is_open = -1;
	i = 0;
	while (cmd[i])
	{
		if (is_open > 0)
			close(is_open);
		if (cmd[i] == '>' && in_quote(cmd, i, 0) == 0)
		{
			cut_re(&mode, &path, &i, cmd);
			is_open = ft_open(mode, path);
			if (is_open < 0)
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd(" : Cannot access file or directory\n", 2);
				return (-1);
			}
		}
		i++;
	}
	stru->append = mode;
	stru->out = path;
	return (mode);
}

int	cut_rre(int *mode, char **path, int *is_open, char **temp)
{
	*mode = 1;
	*path = without_quote(*temp);
	*is_open = open(*path, O_RDONLY);
	if (*is_open < 0)
	{
		ft_putstr_fd(*path, 2);
		ft_putstr_fd(" : Cannot access file or directory\n", 2);
		return (-1);
	}
	if (*temp)
		free(*temp);
	*temp = NULL;
	return (0);
}

int	end_rre(char **heredoc, t_cmd *stru, char *path, int mode)
{
	char	*temp;

	temp = NULL;
	if (heredoc)
	{
		temp = heredoc_c(heredoc, stru, NULL);
		if (!temp)
			return (-2);
		stru->in = temp;
	}
	else
		stru->in = path;
	stru->append = mode;
	return (mode);
}

int	rre_cut2(char *cmd, char ***heredoc, int *i, char *path)
{
	if (path)
		free(path);
	if (cmd[*i + 1] && cmd[*i + 1] == '<')
	{
		*heredoc = ft_realloc(*heredoc, get_next(cmd, *i + 1, 1));
		*i += 2;
		return (1);
	}
	return (0);
}

int	for_rre(char *cmd, t_cmd *stru, char *notVar, int mode)
{
	int		i;
	int		is_open;
	char	**heredoc;
	char	*temp;
	char	*path;

	path = NULL;
	i = -1;
	heredoc = NULL;
	temp = NULL;
	is_open = -1;
	while (cmd[++i])
	{
		if (is_open > 0)
			close(is_open);
		if (cmd[i] == '<' && in_quote(cmd, i, 0) == 0)
		{
			if (rre_cut2(notVar, &heredoc, &i, path) == 1)
				continue ;
			temp = get_next(cmd, i, 0);
			if (cut_rre(&mode, &path, &is_open, &temp) == -1)
				return (-1);
		}
	}
	return (end_rre(heredoc, stru, path, mode));
}
