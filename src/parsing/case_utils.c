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
