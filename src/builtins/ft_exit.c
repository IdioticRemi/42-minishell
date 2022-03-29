/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:18:04 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/29 14:01:17 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_charstr(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required.\n", 2);
			return (2);
		}
	}
	return (ft_atoi(str) % 256);
}

int	ft_exit(t_cmd *cmd)
{
	int	code;

	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_putstr_fd("exit: too many arguments.\n", 2);
		return (1);
	}
	code = ft_charstr(cmd->argv[1]);
	ft_free_cmd(cmd);
	free(g_shell->pids);
	ft_termios_revert();
	ft_free_env(g_shell->env);
	free(g_shell);
	ft_putstr_fd("exit\n", 1);
	exit(code);
}
