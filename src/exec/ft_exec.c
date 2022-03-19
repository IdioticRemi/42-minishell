/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:29:55 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:47:05 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	ft_exec_router(t_cmd *cmd, t_env **env)
{
	int	pid;

	if (cmd->heredoc)
		pid = ft_exec_heredoc(cmd);
	if (!cmd->next || (cmd->out))
	{
		dup2(g_shell->stdout, STDOUT_FILENO);
		pid = ft_exec_single(cmd, env);
		dup2(g_shell->stdin, STDIN_FILENO);
		return (pid);
	}
	return (ft_exec_pipe(cmd, env));
}

void	ft_exec(t_cmd *cmd)
{
	t_cmd	*save;
	int		status;
	size_t	cmdsize;
	size_t	i;

	save = cmd;
	cmdsize = ft_cmdsize(cmd);
	g_shell->pid_count = cmdsize;
	g_shell->pids = ft_calloc(cmdsize, sizeof(int));
	if (!cmd || !cmd->argv || !g_shell->pids)
		return ;
	i = -1;
	while (++i < cmdsize)
	{
		g_shell->pids[i] = ft_exec_router(cmd, &g_shell->env);
		cmd = cmd->next;
	}
	i = -1;
	while (++i < cmdsize)
		waitpid(g_shell->pids[i], &status, 0);
	free(g_shell->pids);
	g_shell->pid_count = 0;
	g_shell->status = WEXITSTATUS(status);
	ft_free_cmd(save);
}
