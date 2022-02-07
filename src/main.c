/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:26 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/07 15:47:34 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_prompt(void)
{
	char	*line;

	line = readline("\033[36mMINISHELL\033[0m> ");
	if (!line)
	{
		printf("exit\n");
		free(g_shell);
		exit(0);
	}
	add_history(line);
	ft_check(line);
	free(line);
}

static void	ft_signal(int sig)
{
	char	*empty;

	if (g_shell->pid_count > 0)
		while (--g_shell->pid_count)
			kill(g_shell->pids[g_shell->pid_count], sig);
	empty = ft_calloc(1, 1);
	write(1, "\n", 1);
	rl_replace_line(empty, 0);
	rl_on_new_line();
	rl_redisplay();
	free(empty);
}

int	main(void)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
		return (1);
	g_shell->stdin = dup(STDIN_FILENO);
	g_shell->stdout = dup(STDOUT_FILENO);
	g_shell->stderr = dup(STDERR_FILENO);
	g_shell->pid_count = 0;
	g_shell->pids = NULL;
	g_shell->env = NULL;
	signal(SIGQUIT, ft_signal);
	signal(SIGINT, ft_signal);
	while (1)
		ft_prompt();
	free(g_shell);
	return (0);
}
