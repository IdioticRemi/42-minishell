/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:23:27 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/03 11:17:24 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_dup(t_cmd *cmd)
{
	int	in;
	int	out;

	if (cmd->in && !cmd->heredoc)
	{
		in = open(cmd->in, O_RDONLY, 0777);
		if (in < 0)
			exit(1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->out)
	{
		out = open(cmd->out, O_WRONLY | O_CREAT | (
					O_TRUNC * !cmd->append) | (O_APPEND * cmd->append), 0777);
		if (out < 0)
			exit(1);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}
