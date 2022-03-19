/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:40:46 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 18:40:46 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug(t_cmd *cmd)
{
	int	i;
	int	y;

	y = 0;
	while (cmd != NULL)
	{
		i = -1;
		printf("========= %d ==========\n", y);
		printf("in : %s\n", cmd->in);
		printf("out : %s\n", cmd->out);
		if (cmd->argv && cmd->argv[0])
			while (cmd->argv[++i])
				printf("args : %s\n", cmd->argv[i]);
		else
			printf("args : %s\n", NULL);
		printf(">> : %d\n", cmd->append);
		printf("heredoc : %d\n", cmd->heredoc);
		cmd = cmd->next;
		y++;
	}
}
