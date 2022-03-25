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

int	white_spaces(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i == 0)
		return (1);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
		i--;
	}
	return (i);
}

char	*get_first(char *cmd_b)
{
	int	i;

	i = 0;
	while (cmd_b[i] && (cmd_b[i] != ' ' || in_quote(cmd_b, i, 0) == 1) && \
		cmd_b[i] != '\n')
		i++;
	return (ft_substr(cmd_b, 0, i));
}

char	*skip_spaces(char *cmd_b)
{
	int		i;
	char	*res;

	i = 0;
	if (white_spaces(cmd_b) == 0)
		return (cmd_b);
	while (cmd_b[i] && cmd_b[i] == ' ')
		i++;
	res = ft_substr(cmd_b, i, ft_strlen(cmd_b) - i);
	free(cmd_b);
	return (res);
}

void	fill_err(t_cmd *cmd)
{
	cmd->argv = malloc(2 * sizeof(char *));
	cmd->argv[0] = malloc(2);
	cmd->argv[1] = NULL;
	cmd->argv[0][0] = 1;
	cmd->argv[0][1] = 0;
	cmd->heredoc = 0;
	if (cmd->in)
		free(cmd->in);
	cmd->in = NULL;
	if (cmd->out)
		free(cmd->out);
	cmd->out = NULL;
	cmd->next = NULL;
}

void	free_multiple(char *one, char *two, char *tree, char *four)
{
	if (one)
		free(one);
	if (two)
		free(two);
	if (tree)
		free(tree);
	if (four)
		free(four);
}

void	fill_cmd(char *cmd_b, t_cmd *cmd)
{
	char	*cmd_true;
	char	*cmd_true_true;
	char	*temp;
	int		err[2];

	cmd_true_true = 0;
	temp = skip_spaces(ft_strdup(cmd_b));
	free(cmd_b);
	cmd_true = with_var(temp, NULL, NULL, 0);
	err[0] = for_rre(cmd_true, cmd, NULL, 0);
	err[1] = for_re(cmd_true, cmd, NULL, 0);
	if ((err[0] == -1 && err[1] == -1) || err[0] == -2)
	{
		fill_err(cmd);
		free_multiple(cmd_true, temp, NULL, NULL);
		return ;
	}
	cmd_true_true = conv_redir(cmd_true);
	cmd_true_true = skip_spaces(cmd_true_true);
	cmd->argv = conv_args(cmd_true_true);
	cmd->argv[0] = get_first(cmd_true_true);
	without_quote_args(cmd);
	free_multiple(cmd_true_true, cmd_true, temp, NULL);
	cmd->next = NULL;
}

void	throw_cases(char *cmd_b, t_cmd *cmd)
{
	char	**b_sep;
	int		i;

	b_sep = ft_split_quote(cmd_b, '|');
	i = 0;
	if (!b_sep[i])
	{
		ft_default_cmd(cmd);
		cmd->argv = malloc(1);
		cmd->argv = NULL;
	}
	while (b_sep[i])
	{
		fill_cmd(b_sep[i], cmd);
		if (b_sep[i + 1])
		{
			cmd->next = malloc(sizeof(t_cmd));
			if (!cmd->next)
				return ;
			ft_default_cmd(cmd->next);
		}
		cmd = cmd->next;
		i++;
	}
	free(b_sep);
}
