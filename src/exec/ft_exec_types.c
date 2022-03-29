/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:54:32 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/29 13:47:16 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_builtin(t_cmd *cmd, t_env **env)
{
	if (cmd->argv[0][0] == 1)
		return (ft_null());
	else if (ft_strequ(cmd->argv[0], "exit"))
		return (ft_exit(cmd));
	else if (ft_strequ(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	else if (ft_strequ(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, env));
	else if (ft_strequ(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, env));
	else if (ft_strequ(cmd->argv[0], "env"))
		return (ft_env(env));
	else if (ft_strequ(cmd->argv[0], "pwd"))
		return (ft_pwd());
	else if (ft_strequ(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, env));
	return (1);
}

static void	ft_exec_cmd(t_cmd *cmd, t_env **env)
{
	char	**_env;
	char	*path;

	if (ft_is_builtin(cmd))
		exit(ft_exec_builtin(cmd, env));
	_env = ft_env_to_array(env);
	if (ft_strchr(cmd->argv[0], '/'))
		path = cmd->argv[0];
	else
		path = ft_pathfind(cmd->argv[0], _env);
	execve(path, cmd->argv, _env);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno != 2 || (ft_strchr(cmd->argv[0], '/')))
		printf("%s: %s.\n", cmd->argv[0], strerror(errno));
	else
		printf("Command '%s' not found.\n", cmd->argv[0]);
	dup2(g_shell->stdout, STDOUT_FILENO);
	free(path);
	ft_afree((void **) _env);
	if (errno == 2 || errno == EACCES)
		exit((errno == 2) * 127 + (errno == EACCES) * 126);
	exit(1);
}

pid_t	ft_exec_single(t_cmd *cmd, t_env **env, int id)
{
	pid_t	pid;

	if (id == 0 && ft_is_builtin(cmd))
	{
		ft_exec_dup(cmd);
		g_shell->status = ft_exec_builtin(cmd, env);
		dup2(g_shell->stdin, STDIN_FILENO);
		dup2(g_shell->stderr, STDERR_FILENO);
		dup2(g_shell->stdout, STDOUT_FILENO);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid)
		return (pid);
	ft_exec_dup(cmd);
	ft_exec_cmd(cmd, env);
	return (pid);
}

pid_t	ft_exec_pipe(t_cmd *cmd, t_env **env)
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

pid_t	ft_exec_heredoc(t_cmd *cmd)
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
	if (!cmd->in)
		cmd->in = ft_strdup("");
	pid = write(files[1], cmd->in, ft_strlen(cmd->in));
	close(files[0]);
	close(files[1]);
	exit(pid);
	return (pid);
}
