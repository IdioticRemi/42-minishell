/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:08:38 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/22 17:09:15 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	if (cmd->argv[0][0] == 1)
		return (1);
	if (ft_strequ(cmd->argv[0], "echo"))
		return (1);
	if (ft_strequ(cmd->argv[0], "export"))
		return (1);
	if (ft_strequ(cmd->argv[0], "unset"))
		return (1);
	if (ft_strequ(cmd->argv[0], "pwd"))
		return (1);
	if (ft_strequ(cmd->argv[0], "cd"))
		return (1);
	if (ft_strequ(cmd->argv[0], "exit"))
		return (1);
	return (0);
}
