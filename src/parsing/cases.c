/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 16:09:22 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int white_spasce(char *str)
{
	int i;

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

char *get_first(char *cmd_b)
{
	int i;
	
	i = 0;
	while (cmd_b[i] && cmd_b[i] != ' ' && cmd_b[i] != '\n')
		i++;
	return (ft_substr(cmd_b, 0, i));
}

char *skipSpasce(char *cmd_b)
{
	int i;
	char *res;

	i = 0;
	if (white_spasce(cmd_b) == 0)
		return (cmd_b);
	while (cmd_b[i] && cmd_b[i] == ' ')
		i++;
	res = ft_substr(cmd_b, i, ft_strlen(cmd_b) - i);
	free(cmd_b);
	return (res);
}

void fill_cmd(char *cmd_b, t_cmd *cmd)
{
	char *cmd_true;

	cmd_true = skipSpasce(ft_strdup(cmd_b));
	free(cmd_b);
	if (for_re(cmd_true, cmd) == -1)
		for_rre(cmd_true, cmd);
	cmd_true = conv_redir(cmd_true);
	cmd->argv = conv_args(cmd_true);
	cmd->argv[0] = get_first(cmd_true);
	free(cmd_true);
	cmd->next = NULL;
}

void throw_cases(char *cmd_b, t_cmd *cmd)
{
	char **b_sep;
	int i;

	b_sep = ft_split(cmd_b, '|');
	i = 0;
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
}
