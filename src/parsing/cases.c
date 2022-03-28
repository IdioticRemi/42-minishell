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
	err[0] = for_rre(cmd_true, cmd, temp, 0);
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
