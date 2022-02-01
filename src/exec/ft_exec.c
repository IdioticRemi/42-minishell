/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:29:55 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/01 16:25:13 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (ft_strchr(cmd->argv[0], '/'))
		path = cmd->argv[0];
	else
		path = ft_pathfind(cmd->argv[0], env);
	execve(path, cmd->argv, env);
	ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd("Path to executable not found for command: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(".\n", 2);
	exit(1);
}

static pid_t	ft_exec_last(t_cmd *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	ft_exec_dup(cmd);
	ft_exec_cmd(cmd, env);
	return (pid);
}

static pid_t	ft_exec_pipe(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		files[2];

	if (pipe(files) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
	{
		dup2(files[0], STDIN_FILENO);
		close(files[0]);
		close(files[1]);
		return (pid);
	}
	dup2(files[1], STDOUT_FILENO);
	close(files[0]);
	close(files[1]);
	ft_exec_dup(cmd);
	ft_exec_cmd(cmd, env);
	return (pid);
}

static pid_t	ft_exec_router(t_shell *shell, t_cmd *cmd, char **env)
{
	int	pid;

	if (!cmd->next || (cmd->out))
	{
		dup2(shell->stdout, STDOUT_FILENO);
		pid = ft_exec_last(cmd, env);
		dup2(shell->stdin, STDIN_FILENO);
		return (pid);
	}
	else
		return (ft_exec_pipe(cmd, env));
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
