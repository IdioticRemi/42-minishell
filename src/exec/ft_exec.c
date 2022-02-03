/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:29:55 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/03 11:28:17 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_exec_router(t_shell *shell, t_cmd *cmd, char **env)
{
	int	pid;
	
	if (cmd->heredoc)
		pid = ft_exec_heredoc(cmd);
	if (!cmd->next || (cmd->out))
	{
		dup2(shell->stdout, STDOUT_FILENO);
		pid = ft_exec_single(shell, cmd, env);
		dup2(shell->stdin, STDIN_FILENO);
		return (pid);
	}
	return (ft_exec_pipe(shell, cmd, env));
}

int	ft_exec(t_shell *shell, t_cmd *cmd, char **env)
{
	int		*pids;
	int		status;
	size_t	cmdsize;
	size_t	i;

	cmdsize = ft_cmdsize(cmd);
	pids = ft_calloc(cmdsize, sizeof(int));
	if (!cmd || !cmd->argv || !pids)
		return (-1);
	i = -1;
	while (++i < cmdsize)
	{
		pids[i] = ft_exec_router(shell, cmd, env);
		cmd = cmd->next;
	}
	i = -1;
	while (++i < cmdsize)
		waitpid(pids[i], &status, 0);
	free(pids);
	(void) env;
	return (WEXITSTATUS(status));
}
