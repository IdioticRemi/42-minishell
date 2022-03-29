/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:26 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/29 11:26:00 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_exit(void)
{
	ft_termios_revert();
	ft_free_env(g_shell->env);
	free(g_shell);
	exit(0);
}

static void	ft_prompt(void)
{
	char	*line;
	size_t	i;

	line = readline("\033[36mMINISHELL\033[0m> ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		ft_clean_exit();
	}
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[0] && i < ft_strlen(line) - 1)
	{
		dprintf(2, "'%s' (%lu =?= %lu)\n", line, i, ft_strlen(line));
		add_history(line);
		ft_check(line);
	}
}

static void	ft_signal(int sig)
{
	char	*empty;

	if (g_shell->pid_count > 0)
	{
		while (--g_shell->pid_count)
			kill(g_shell->pids[g_shell->pid_count], sig);
		if (sig == SIGQUIT)
			write(1, "Quit\n", 5);
		else
			write(1, "\n", 1);
		return ;
	}
	if (sig == SIGINT)
	{
		empty = ft_calloc(1, 1);
		write(1, "\n", 1);
		rl_replace_line(empty, 0);
		free(empty);
	}
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **argv, char **env)
{
	char	*shlvl;

	(void) argv;
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	g_shell->stdin = dup(STDIN_FILENO);
	g_shell->stdout = dup(STDOUT_FILENO);
	g_shell->stderr = dup(STDERR_FILENO);
	g_shell->status = 0;
	g_shell->pid_count = 0;
	g_shell->pids = NULL;
	g_shell->env = ft_parse_env(env);
	shlvl = ft_get_env(g_shell->env, "SHLVL");
	ft_set_env(&g_shell->env, ft_strdup("SHLVL"), ft_itoa(
			ft_atoi(shlvl) + 1 + (0 * ac)));
	free(shlvl);
	ft_termios_init();
	signal(SIGQUIT, ft_signal);
	signal(SIGINT, ft_signal);
	while (1)
		ft_prompt();
}
