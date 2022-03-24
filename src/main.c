/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:26 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 16:40:29 by tjolivea         ###   ########lyon.fr   */
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

	line = readline("\033[36mMINISHELL\033[0m> ");
	if (!line)
	{
		printf("exit\n");
		ft_clean_exit();
	}
	add_history(line);
	ft_check(line);
}

static void	ft_signal(int sig)
{
	char	*empty;

	if (g_shell->pid_count > 0)
	{
		while (--g_shell->pid_count)
			kill(g_shell->pids[g_shell->pid_count], sig);
		write(1, "\n", 1);
		return ;
	}
	empty = ft_calloc(1, 1);
	if (sig == SIGQUIT)
		return ;
	write(1, "\n", 1);
	rl_replace_line(empty, 0);
	rl_on_new_line();
	rl_redisplay();
	free(empty);
}

int	main(int ac, char **argv, char **env)
{
	char	*shlvl;

	(void) ac;
	(void) argv;
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	g_shell->stdin = dup(STDIN_FILENO);
	g_shell->stdout = dup(STDOUT_FILENO);
	g_shell->stderr = dup(STDERR_FILENO);
	g_shell->pid_count = 0;
	g_shell->pids = NULL;
	g_shell->env = ft_parse_env(env);
	if (!g_shell->env)
		ft_clean_exit();
	shlvl = ft_get_env(g_shell->env, "SHLVL");
	ft_set_env(&g_shell->env, ft_strdup("SHLVL"), ft_itoa(
			ft_atoi(shlvl) + 1));
	free(shlvl);
	ft_termios_init();
	signal(SIGQUIT, ft_signal);
	signal(SIGINT, ft_signal);
	while (1)
		ft_prompt();
}
