/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:18:04 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 16:40:22 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd *cmd)
{
	ft_free_cmd(cmd);
	free(g_shell->pids);
	ft_clean_exit();
}
