/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:12:56 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 16:19:06 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_default_cmd(t_cmd *cmd)
{
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->status = 0;
	cmd->argv = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->next = NULL;
}
